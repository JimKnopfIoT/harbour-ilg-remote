import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Configuration 1.0
import harbour.lgremote 1.0
import "pages"
import "cover"

ApplicationWindow {
    id: app

    /* Die Geraeteliste liegt als JSON in einem einzigen Einstellungswert.
       Jeder Eintrag: name, host, mac, key. Der Kopplungsschluessel gehoert
       zum Geraet - sonst muesste man sich bei jedem Wechsel neu anmelden. */
    ConfigurationValue {
        id: cfgDevices
        key: "/apps/harbour-lgremote/devices"
        defaultValue: ""
    }
    ConfigurationValue {
        id: cfgCurrent
        key: "/apps/harbour-lgremote/current"
        defaultValue: 0
    }

    /* Die vier Direktaufrufe des Zahlenblocks, ebenfalls als JSON. Jeder
       Eintrag: kind (app oder input), id, label, img. img ist ein Bild aus
       qml/images; selbst belegte Kacheln tragen ihre Beschriftung. */
    ConfigurationValue {
        id: cfgTiles
        key: "/apps/harbour-lgremote/tiles"
        defaultValue: ""
    }

    /* Bestand aus der Fassung mit nur einem Geraet - wird einmalig uebernommen.
       Ohne Vorgabewerte: eine Adresse und eine MAC, die dem Nutzer nicht
       gehoeren, waeren schlimmer als gar keine. Eine mitgelieferte MAC hat
       ausserdem verhindert, dass die vom Fernseher gemeldete je eingetragen
       wurde - und das Weckpaket ging an ein fremdes Geraet. */
    ConfigurationValue { id: oldHost; key: "/apps/harbour-lgremote/host";      defaultValue: "" }
    ConfigurationValue { id: oldMac;  key: "/apps/harbour-lgremote/mac";       defaultValue: "" }
    ConfigurationValue { id: oldKey;  key: "/apps/harbour-lgremote/clientKey"; defaultValue: "" }

    property var devices: []
    property int currentIndex: 0
    property var tiles: []

    /* Fuenf frei belegbare Kacheln; die sechste ist fest das Bildschirmfoto. */
    readonly property var defaultTiles: [
        { "kind": "app", "id": "com.webos.app.livetv",  "label": "TV",       "img": "tv.png" },
        { "kind": "app", "id": "youtube.leanback.v4",   "label": "YouTube",  "img": "youtube.png" },
        { "kind": "app", "id": "",                      "label": "",         "img": "" },
        { "kind": "app", "id": "org.jellyfin.webos",    "label": "Jellyfin", "img": "jellyfin.png" },
        { "kind": "app", "id": "",                      "label": "",         "img": "" }
    ]

    readonly property var device: (currentIndex >= 0 && currentIndex < devices.length)
                                  ? devices[currentIndex] : null
    readonly property string host: device ? device.host : ""
    readonly property string mac:  device ? device.mac  : ""
    /* Alle anfunkbaren Adressen des Geraets. Von Hand Eingetragenes gilt
       allein - da hat jemand entschieden, und das wird nicht ueberstimmt. */
    readonly property var macList: {
        if (!device) return []
        if (device.macFrom === "hand" && device.mac && device.mac.length > 0)
            return [device.mac]
        if (device.macs && device.macs.length > 0)
            return device.macs.split(" ")
        return (device.mac && device.mac.length > 0) ? [device.mac] : []
    }
    readonly property string deviceName: device ? device.name : ""

    function loadDevices() {
        var list = []
        if (cfgDevices.value && cfgDevices.value.length > 0) {
            try { list = JSON.parse(cfgDevices.value) }
            catch (e) {
                errorLog.add(qsTr("Devices"), qsTr("the stored device list is unreadable"),
                             String(e))
                list = []
            }
        }
        // Nur uebernehmen, wenn aus der alten Fassung wirklich etwas dasteht
        if (list.length === 0 && oldHost.value && oldHost.value.length > 0) {
            list = [{ "name": qsTr("Television"), "host": oldHost.value,
                      "mac": oldMac.value, "key": oldKey.value, "cert": "",
                      "macFrom": oldMac.value && oldMac.value.length > 0 ? "hand" : "" }]
        }
        /* Felder vereinheitlichen - aeltere Eintraege kennen macFrom nicht.
           Wer damals von Hand eine MAC eintrug, soll sie behalten. */
        list = list.map(function (d) {
            return { "name": d.name ? d.name : "", "host": d.host ? d.host : "",
                     "mac": d.mac ? d.mac : "", "key": d.key ? d.key : "",
                     "cert": d.cert ? d.cert : "", "macs": d.macs ? d.macs : "",
                     "macFrom": d.macFrom ? d.macFrom : (d.mac && d.mac.length > 0 ? "hand" : "") }
        })
        devices = list
        currentIndex = Math.max(0, Math.min(cfgCurrent.value, list.length - 1))
        applyCurrent()
    }

    function saveDevices() {
        cfgDevices.value = JSON.stringify(devices)
    }

    function applyCurrent() {
        if (!device) return
        tvConn.certFingerprint = device.cert ? device.cert : ""
        tvConn.host = device.host
        tvConn.clientKey = device.key
    }

    function loadTiles() {
        var list = []
        if (cfgTiles.value && cfgTiles.value.length > 0) {
            try { list = JSON.parse(cfgTiles.value) }
            catch (e) {
                errorLog.add(qsTr("Tiles"), qsTr("the stored tiles are unreadable"), String(e))
                list = []
            }
        }
        if (list.length === 0) list = defaultTiles
        while (list.length < 5)
            list.push({ "kind": "app", "id": "", "label": "", "img": "", "icon": "" })
        // Felder vereinheitlichen - aeltere Eintraege koennen welche vermissen
        tiles = list.slice(0, 5).map(function (t) {
            return { "kind": t.kind ? t.kind : "app", "id": t.id ? t.id : "",
                     "label": t.label ? t.label : "", "img": t.img ? t.img : "",
                     "icon": t.icon ? t.icon : "" }
        })
    }

    function saveTiles() { cfgTiles.value = JSON.stringify(tiles) }

    /* Das Symbol wird beim Belegen geholt, nicht erst beim Anzeigen: sonst
       bleibt die Kachel leer, bis die Auswahlliste es einmal geladen hat. */
    function setTile(i, kind, id, label, icon) {
        if (i < 0 || i >= tiles.length) return
        var list = tiles.slice()
        list[i] = { "kind": kind, "id": id, "label": label, "img": "", "icon": icon }
        tiles = list
        saveTiles()
        if (icon && icon.length > 0)
            icons.prefetch(icon)
        else if (id && id.length > 0)
            errorLog.add(qsTr("Tile"), qsTr("the TV names no icon for this entry"), label)
    }

    function resetTiles() {
        tiles = defaultTiles
        saveTiles()
    }

    function selectDevice(i) {
        if (i < 0 || i >= devices.length) return
        currentIndex = i
        cfgCurrent.value = i
        applyCurrent()
        tvConn.connectTv()
    }

    /* Schluessel und Zertifikat kommen erst waehrend der Verbindung - sie
       muessen beim richtigen Geraet landen. */
    function storeKey(k) {
        if (!device || device.key === k) return
        var list = devices.slice()
        list[currentIndex].key = k
        devices = list
        saveDevices()
    }

    function storeCert(f) {
        if (!device || device.cert === f) return
        var list = devices.slice()
        list[currentIndex].cert = f
        devices = list
        saveDevices()
    }

    /* Die MAC kommt vom verbundenen Fernseher. Von Hand Eingetragenes bleibt
       stehen - was die App selbst geholt hat, darf sie berichtigen. */
    function storeMacs(macs) {
        if (!device || !macs || macs.length === 0) return
        var neu = macs.join(" ")
        var vonHand = device.macFrom === "hand" && device.mac && device.mac.length > 0
        if (device.macs === neu && (vonHand || device.mac === macs[0])) return
        var list = devices.slice()
        list[currentIndex].macs = neu
        if (!vonHand) {
            list[currentIndex].mac = macs[0]
            list[currentIndex].macFrom = "tv"
        }
        devices = list
        saveDevices()
    }

    function addDevice(name, host, mac) {
        var list = devices.slice()
        list.push({ "name": name, "host": host, "mac": mac, "key": "", "cert": "",
                    "macs": "", "macFrom": mac && mac.length > 0 ? "hand" : "" })
        devices = list
        saveDevices()
        return list.length - 1
    }

    function updateDevice(i, name, host, mac) {
        if (i < 0 || i >= devices.length) return
        var list = devices.slice()
        list[i].name = name
        list[i].host = host
        // Von Hand geaendert heisst von Hand - auch das Leeren des Feldes
        if (mac !== list[i].mac)
            list[i].macFrom = mac && mac.length > 0 ? "hand" : ""
        list[i].mac = mac
        devices = list
        saveDevices()
        if (i === currentIndex) applyCurrent()
    }

    /* Kopplung eines einzelnen Geraets loesen: Schluessel und gemerktes
       Zertifikat weg, der Eintrag bleibt. Er wird ja nicht falsch dadurch. */
    function resetPairing(i) {
        if (i < 0 || i >= devices.length) return
        var list = devices.slice()
        list[i].key = ""
        list[i].cert = ""
        devices = list
        saveDevices()
        if (i === currentIndex) {
            // Bewusst kein neuer Versuch: die Abfrage am Fernseher soll der
            // Nutzer ausloesen, nicht die App hinter seinem Ruecken
            tvConn.disconnectTv()
            applyCurrent()
        }
    }

    function removeDevice(i) {
        if (i < 0 || i >= devices.length) return
        var list = devices.slice()
        list.splice(i, 1)
        devices = list
        saveDevices()
        if (list.length === 0) {
            // Nichts mehr da, worauf sich eine Verbindung beziehen koennte
            currentIndex = 0
            cfgCurrent.value = 0
            tvConn.disconnectTv()
            tvConn.host = ""
            tvConn.clientKey = ""
            tvConn.certFingerprint = ""
            return
        }
        selectDevice(Math.max(0, Math.min(currentIndex, list.length - 1)))
    }

    LgTv {
        id: tvConn
        onClientKeyChanged: app.storeKey(clientKey)
        onMacsDiscovered: app.storeMacs(macs)
        // Der Symbolabruf braucht denselben Fingerabdruck
        onCertFingerprintChanged: {
            app.storeCert(certFingerprint)
            icons.fingerprint = certFingerprint
        }
        onCaptureReady: icons.saveToGallery(url, "lgremote-"
                        + Qt.formatDateTime(new Date(), "yyyyMMdd-hhmmss") + ".jpg")
    }

    Connections {
        target: icons
        onSaved: tvConn.note(qsTr("Screenshot saved: %1").arg(path))
        onSaveFailed: tvConn.note(message)
    }

    initialPage: Component { RemotePage { tv: tvConn; window: app } }
    cover: Component { CoverPage { tv: tvConn } }
    // Die Fernbedienung dreht nicht mit
    allowedOrientations: Orientation.Portrait

    Component.onCompleted: {
        loadDevices()
        loadTiles()
        icons.fingerprint = tvConn.certFingerprint
        if (host.length > 0) tvConn.connectTv()
    }
}
