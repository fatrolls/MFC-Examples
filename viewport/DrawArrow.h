class DrawArrow {
    public:
       typedef enum {ARROW_NONE, ARROW_N, ARROW_S, ARROW_W, ARROW_E, ARROW_NW, ARROW_NE, ARROW_SW, ARROW_SE} Direction;
       static void Draw(CDC & dc, CRect r, Direction direction);
};

