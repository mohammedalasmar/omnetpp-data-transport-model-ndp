QT.webview.VERSION = 5.6.1
QT.webview.MAJOR_VERSION = 5
QT.webview.MINOR_VERSION = 6
QT.webview.PATCH_VERSION = 1
QT.webview.name = QtWebView
QT.webview.module = QtWebView
QT.webview.libs = $$QT_MODULE_LIB_BASE
QT.webview.includes = $$QT_MODULE_LIB_BASE/QtWebView.framework/Headers
QT.webview.frameworks = $$QT_MODULE_LIB_BASE
QT.webview.bins = $$QT_MODULE_BIN_BASE
QT.webview.libexecs = $$QT_MODULE_LIBEXEC_BASE
QT.webview.plugins = $$QT_MODULE_PLUGIN_BASE
QT.webview.imports = $$QT_MODULE_IMPORT_BASE
QT.webview.qml = $$QT_MODULE_QML_BASE
QT.webview.depends =
QT.webview.run_depends = webengine_private quick_private gui_private
QT.webview.module_config = v2 lib_bundle
QT.webview.DEFINES = QT_WEBVIEW_LIB
QT_MODULES += webview
