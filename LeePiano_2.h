class LeeKey : public Component {

    public :

        // constructor & destructor
        LeeKey (int index, bool blackOrWhite) : keyIndex(index), isWhiteKey(blackOrWhite) {}
        ~LeeKey()   {}

        // mouse handler
        
        void 	mouseEnter    (const MouseEvent&) override {
        
            isHovered = true;
            repaint();
        
        }
        void 	mouseExit     (const MouseEvent&) override {
        
            isHovered = false;
            repaint();
        
        }
        void 	mouseDown     (const MouseEvent&) override {
        
            isPressed = !isPressed;
            repaint();
        
        }

        // drawer
        void paint(Graphics& g) override {

            // prepare parameters.
            Rectangle<float>    localBound{ getLocalBounds().toFloat() };
            Colour              keyColor;
            Colour              borderColor;
            float               borderWidth;


            switch (isPressed) {

                case 0 : keyColor = keyOffColor; borderColor = borderOffColor; borderWidth = borderOffWidth; break;
                case 1 : keyColor = keyOnColor ; borderColor = borderOnColor ; borderWidth = borderOnWidth ; break;

            }


            switch (isHovered) {

                case 1 : borderColor = borderHoverColor; borderWidth = borderHoverWidth; break;

            }

            // draw !

                // create path.
                Path key;
                key.addRoundedRectangle(localBound.getX() + (borderWidth / 2.0f), localBound.getY() + (borderWidth / 2.0f), localBound.getWidth() - borderWidth, localBound.getHeight() - borderWidth, cornerSize);

                // draw key.
                g.setColour(keyColor);
                g.fillPath(key);

                // draw border.
                g.setColour(borderColor);
                g.strokePath(key, PathStrokeType(borderWidth));
            
               
        }

    private :
    
        int             keyIndex                    { /* by constructor */};
        bool            isWhiteKey                  { /* by constructor : false - black key, true - white key */};        
        bool            isVisible                   { false };
        bool            isPressed                   { false };
        bool            isHovered                   { false };
        bool            isDragTarget                { false };
        bool            isDropTarget                { false };

        const std::array<Colour, 12> keyColorPicker{

            Colour  {209, 67, 69},    // c
                    {209, 105, 67},   // c#
                    {213, 146, 31},   // d
                    {151, 150, 31},   // d#
                    {87, 170, 85},    // e
                    {48, 149, 96},    // f
                    {31, 147, 162},   // f#
                    {63, 158, 237},   // g
                    {29, 124, 236},   // g#
                    {152, 85, 249},   // a
                    {209, 76, 237},   // a#
                    {218, 65, 133}    // b

        };

        const Colour    keyOnColor                  { keyColorPicker[keyIndex % 12] };
        const Colour    keyOffColor                 { 25, 25, 25 };
        const Colour    keyDragTargetColor          { 200, 200, 200 };
        const Colour    keyDropTargetColor          { keyOnColor.withAlpha(1.0f) };

        const Colour    borderOnColor               { 25, 25, 25 };
        const Colour    borderOffColor              { keyOnColor.withBrightness(0.4f) };
        const Colour    borderHoverColor            { 200, 200, 200};
        const Colour    borderDragTargetColor       { 30, 20, 30 };
        const Colour    borderDropTargetColor       { 50, 100, 30 };

        const float     cornerSize                  { 6.0f };
        const float     borderOffWidth              { 2.0f };
        const float     borderOnWidth               { 4.0f };
        const float     borderHoverWidth            { 4.0f };
        const float     borderDragTargetWidth       { borderOffWidth * 3.0f };
        const float     borderDropTargetWidth       { borderOffWidth * 4.0f };
        
       
};

class LeePiano : public Component {

    public :

        LeePiano()  {
            
            // 1. create keys LeeKey's instance.
            for (int i = 0; i < amount; ++i) {

                keys[i] = std::make_unique<LeeKey>(i, isWhiteKey(i));

            }

            // 2. make visible.
            for (int i = 0; i < amountVisible; ++i) {

                addAndMakeVisible(*keys[i]);

            }
        
        }

        ~LeePiano() {}

        // own functions
        bool isWhiteKey(int index) {

            const int relativePitch { index % 12 };

            switch (relativePitch) {

                case 1:
                case 3:
                case 6:
                case 8:
                case 10: return false; // black 
                default: return true;  // white
 
            }
        }

        float calWhiteKeyWidth(int amt) {

            return 1.0f / ((static_cast<float>(amt) / 12.0f) * 7.0f);

        }

        // set bounds.
        void resized() override {

            int whiteKeyCounter { 0 };
            const float whiteKeyWidth { calWhiteKeyWidth(amountVisible) };

            for (int i = 0; i < amountVisible; ++i) {

                float whiteKeyX { whiteKeyWidth * static_cast<float>(whiteKeyCounter) };

                if (isWhiteKey(i)) {

                    keys[i]->setBoundsRelative(whiteKeyX + (whiteKeyGap / 2.0f), whiteKeyGap / 2.0f, whiteKeyWidth - whiteKeyGap, whiteKeyHeight - whiteKeyGap);
                    whiteKeyCounter++;

                }

                else {

                    float blackKeyX { whiteKeyX + (whiteKeyWidth / 2.0f) - whiteKeyWidth };

                    // E, F shoudn't have black key between. (if previous note is F )
                    if ((whiteKeyCounter % 7) == 3) {

                        blackKeyX = whiteKeyX + (whiteKeyWidth / 2.0f);

                    }

                    keys[i]->setBoundsRelative(blackKeyX + (blackKeyGap / 2.0f) , 0.0f, whiteKeyWidth - blackKeyGap, blackKeyHeight - blackKeyGap);
                    keys[i]->setAlwaysOnTop(true);


                }

            }


        }


    private :
        
        std::array<std::unique_ptr<LeeKey>, 84> keys;

        const int   amount              { 84 };
              int   amountVisible       { 36 };
        const float whiteKeyHeight      { 1.0f };
        const float blackKeyHeight      { 0.5f };
        const float whiteKeyGap         { 0.002f };   // relative (0. 1.)
        const float blackKeyGap         { 0.004f };     // relative (0. 1.)

};