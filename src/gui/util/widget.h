class widget
{
    public:
        widget(widget *parent);
        ~widget();
        void addChild(widget *child);


        widget *parent;
        widget **children;
        int numChildren;
        int topleft[2];
        int size[2];
        int click(int, int);
        int draw();
};