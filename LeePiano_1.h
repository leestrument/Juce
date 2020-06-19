class LeePiano : public Component {

    public :

        class LeeKey : public Component {

            public:

            LeeKey(int noteNumber, Colour& keyColor) : note(noteNumber), color(keyColor) {}
            ~LeeKey() {}

            void paint(Graphics& g) override {

                Rectangle<float> localBound { getLocalBounds().toFloat() };

                g.setColour(color);
                g.fillRoundedRectangle(localBound, 8.0f);

                // draw boarder only if this key is black key.
                int relativeNote { note % 12 };

                if (relativeNote == 1 || relativeNote == 3 || relativeNote == 5 || relativeNote == 8 || relativeNote == 10) {

                    // create path.
                    Path path;
                    float lineThickness { 2.5f };
                    float cornerSize {8.0f};
                    float d { lineThickness / 2.0f };
                    path.addRoundedRectangle(localBound.getX() + d, localBound.getY() + d, localBound.getWidth() - lineThickness, localBound.getHeight() - lineThickness, cornerSize);

                    // stroke path.
                    g.setColour(Colour(10, 10, 10));
                    g.strokePath(path, PathStrokeType(lineThickness));
                   
                }

            }

            private:

                int note;
                Colour color;

        };

        LeePiano() {

            // create LeeKey's instance.
            for (int i = 0; i < amount; ++i) {

                int noteNumber {i};
                Colour keyColor { colors[i % 12] };

                keys.push_back(std::make_unique<LeeKey>(noteNumber, keyColor));

            }

            // make them visible.
            for (auto& key : keys) {

                addAndMakeVisible(*key);

            }

        }

        ~LeePiano()         {}

        void resized() override {
        
            std::array<int, 5> blackIndex{ 1, 3, 5, 8, 10 };
            int whiteKeyCounter { 0 };
            float whiteW { 1.0f / ((static_cast<float>(amount) / 12.0f) * 7.0f) };
            float whiteH { 1.0f };
            float whiteGap { 0.00125f };
            float blackGap { 0.0015f };
        
            // set bounds of each key.
            for (int i = 0; i < amount; ++i) {

                // check if "i" is black or white key.
                bool isWhiteKey { true };
                for (auto each : blackIndex) {

                    if ((i % 12) == each) {

                        isWhiteKey = false;
                        break;

                    }

                }
                
                // set whiteX and blackX, blackH.
                float whiteX { static_cast<float>(whiteKeyCounter) * whiteW };
                
                if (isWhiteKey) {

                    keys[i]->setBoundsRelative(whiteX + whiteGap, whiteGap, whiteW - (whiteGap * 2.0f), whiteH - (whiteGap * 2.0f));
                    whiteKeyCounter++;

                }

                else {

                    float blackX { whiteX + (whiteW / 2.0f) - whiteW };

                    // if previous note is F.
                    if ((whiteKeyCounter % 7) == 3) {

                        blackX = whiteX + (whiteW / 2.0f);

                    }

                    float blackH { whiteH / 2.0f };

                    keys[i]->setBoundsRelative(blackX + blackGap, 0.0f, whiteW - (blackGap * 2.0f), blackH - (blackGap * 2.0f));
                    keys[i]->setAlwaysOnTop(true);

                }

            }
        
        }

    private :

        int amount { 48 };
        std::vector<std::unique_ptr<LeeKey>> keys;
        std::array<Colour, 12> colors {

            Colour{209, 67, 69},    // c
            Colour{209, 105, 67},   // c#
            Colour{213, 146, 31},   // d
            Colour{151, 150, 31},   // d#
            Colour{87, 170, 85},    // e
            Colour{48, 149, 96},    // f
            Colour{31, 147, 162},   // f#
            Colour{63, 158, 237},   // g
            Colour{29, 124, 236},   // g#
            Colour{152, 85, 249},   // a
            Colour{209, 76, 237},   // a#
            Colour{218, 65, 133}    // b

        };

};