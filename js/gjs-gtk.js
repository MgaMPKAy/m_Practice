const Gtk = imports.gi.Gtk

function hello(widget) {
    log("Hello, World");
}

function onDestroy(widget) {
    log("destroy signal occured");
    Gtk.main_quit();
}

Gtk.init(0, null);

let win = new Gtk.Window({type: Gtk.WindowType.TOPLEVEL});
win.connect("destroy", onDestroy);

let button = new Gtk.Button({label: "Hello World"});

button.connect("clicked", hello);
button.connect("clicked", function() {
    win.destroy();
});

win.add(button);
button.show();
win.show();
Gtk.main()
