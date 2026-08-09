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

    // Bestand aus der Fassung mit nur einem Geraet - wird einmalig uebernommen
    ConfigurationValue { id: oldHost; key: "/apps/harbour-lgremote/host";      defaultValue: "" }
    ConfigurationValue { id: oldMac;  key: "/apps/harbour-lgremote/mac";       defaultValue: "" }
    ConfigurationValue { id: oldKey;  key: "/apps/harbour-lgremote/clientKey"; defaultValue: "" }

    property var devices: []
    property int currentIndex: 0

    readonly property var device: (currentIndex >= 0 && currentIndex < devices.length)
                                  ? devices[currentIndex] : null
    readonly property string host: device ? device.host : ""
    readonly property string mac:  device ? device.mac  : ""
    readonly property string deviceName: device ? device.name : ""

    function loadDevices() {
        var list = []
        if (cfgDevices.value && cfgDevices.value.length > 0) {
            try { list = JSON.parse(cfgDevices.value) } catch (e) { list = [] }
        }
        if (list.length === 0) {
            list = [{ "name": "Fernseher", "host": oldHost.value,
                      "mac": oldMac.value, "key": oldKey.value }]
        }
        devices = list
        currentIndex = Math.max(0, Math.min(cfgCurrent.value, list.length - 1))
        applyCurrent()
    }

    function saveDevices() {
        cfgDevices.value = JSON.stringify(devices)
    }

    function applyCurrent() {
        if (!device) return
        tvConn.host = device.host
        tvConn.clientKey = device.key
    }

    function selectDevice(i) {
        if (i < 0 || i >= devices.length) return
        currentIndex = i
        cfgCurrent.value = i
        applyCurrent()
        tvConn.connectTv()
    }

    /* Der Fernseher liefert den Schluessel erst nach der Bestaetigung -
       er muss beim richtigen Geraet landen. */
    function storeKey(k) {
        if (!device || device.key === k) return
        var list = devices.slice()
        list[currentIndex].key = k
        devices = list
        saveDevices()
    }

    function addDevice(name, host, mac) {
        var list = devices.slice()
        list.push({ "name": name, "host": host, "mac": mac, "key": "" })
        devices = list
        saveDevices()
        return list.length - 1
    }

    function updateDevice(i, name, host, mac) {
        if (i < 0 || i >= devices.length) return
        var list = devices.slice()
        list[i].name = name
        list[i].host = host
        list[i].mac = mac
        devices = list
        saveDevices()
        if (i === currentIndex) applyCurrent()
    }

    function removeDevice(i) {
        if (i < 0 || i >= devices.length || devices.length === 1) return
        var list = devices.slice()
        list.splice(i, 1)
        devices = list
        saveDevices()
        selectDevice(Math.max(0, Math.min(currentIndex, list.length - 1)))
    }

    LgTv {
        id: tvConn
        onClientKeyChanged: app.storeKey(clientKey)
    }

    initialPage: Component { RemotePage { tv: tvConn; window: app } }
    cover: Component { CoverPage { tv: tvConn } }
    allowedOrientations: defaultAllowedOrientations

    Component.onCompleted: {
        loadDevices()
        tvConn.connectTv()
    }
}
