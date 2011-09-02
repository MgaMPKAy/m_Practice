const Clutter = imports.gi.Clutter;
const Tweener = imports.tweener.tweener;

function click(actor, ev) {
    let properties = {  time: 2.0,
                        x: texture.x+100,
                        y: texture.y+100,
                        scale_x: 0.8,
                        scale_y: 0.8,
			transition: 'easeInBounce',
                        opacity: 0
                     };
    Tweener.addTween(texture, properties);
    print('Clicked!');
    return true;
}

function quit(actor) {
    Clutter.main_quit();
}

Clutter.init(0, null);
let stage = new Clutter.Stage();
let texture = new Clutter.Texture({ filename: 'test.png',
                                    reactive: true });
texture.connect('button-press-event', click);
stage.connect('destroy', quit);
stage.add_actor(texture);
stage.show();

Clutter.main();