#include <JuceHeader.h>

/* Child */
class LeeGrid : public Component {

    public :

        LeeGrid(ValueTree v) : valueTree(v) {


        }

        ~LeeGrid() {}

        void paint(Graphics& g) override {

            g.fillAll(Colours::darkmagenta);

        }

    private :

        ValueTree valueTree;

};

/* Parent */
class Plugin : public AudioProcessor {

    public :

        /* 
        
            Constructor 
            
            for Instrument : AudioProcessor(BusesProperties().withOutput("Output", AudioChannelSet::stereo(), true))
            for Audio FX   : AudioProcessor(BusesProperties().withInput("Input", AudioChannelSet::stereo(), true).withOutput("Output", AudioChannelSet::stereo(), true))
        
        */
        
        Plugin() 
        :   AudioProcessor(BusesProperties().withOutput("Output", AudioChannelSet::stereo(), true)), 
            valueTreeState(*this, nullptr, "valueTreeState", createParameterLayout()) {}

        /* Destructor */
        ~Plugin() {}

        /* ParameterLayout */
        AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {

            std::vector<std::unique_ptr<RangedAudioParameter>> parameters;

            /* Add your parameter here to automate in DAW. Below is example. */
            parameters.push_back(std::make_unique<AudioParameterBool>("test", "Test", false));

            return  { parameters.begin(), parameters.end() };

        }

        /* Pure Virtual */

            /* Preference */
            const String            getName             ()		                                                        const override  { return "Loptimist"; }
            const String	           getProgramName      (int index)                                                 override        { return "Loptimist"; }
            int                     getNumPrograms      ()                                                          override        { return 1; }
            int                     getCurrentProgram   ()                                                          override        { return 0; }
            double                  getTailLengthSeconds()                                                          const override  { return 0.0f; }
            bool                    acceptsMidi         ()                                                          const override  { return true; }
            bool                    producesMidi        ()                                                          const override  { return true; }
            bool                    isMidiEffect        ()                                                          const override  { return false; }
            void                    getStateInformation (MemoryBlock& destData)                                     override        { /* do nothing?? */ }
            void                    setStateInformation (const void* data, int sizeInBytes)                         override        { /* do nothing?? */ }
            void                    setCurrentProgram   (int index)                                                 override        { /* do nothing?? */ }
            void                    changeProgramName   (int index, const String& newName)                          override        { /* do nothing?? */ }
        
            /* Editor */
            bool                    hasEditor           ()                                                          const override  { return true; }
            AudioProcessorEditor*   createEditor        ()                                                          override;       /* Implement after Gui implementation. */
        
            /* Processor */
            void                    prepareToPlay       (double sampleRate, int samplesPerBlock)                    override        { /* do nothing?? */ }
            void                    processBlock        (AudioBuffer<float>& audioBuffer, MidiBuffer& midiBuffer)   override        { /* do nothing?? */ }
            void                    releaseResources    ()                                                          override        { /* do nothing?? */ }

    private :
    
        AudioProcessorValueTreeState valueTreeState;
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Plugin)

};
class Gui : public AudioProcessorEditor {

    public :
        
        /* Constructor*/
        Gui(Plugin& p, AudioProcessorValueTreeState& vts) 
        :   AudioProcessorEditor(&p),
            pluginReference(p),
            valueTreeStateReference(vts),
            leeGrid(vts.state) {
        
            addAndMakeVisible(leeGrid);
            setSize(guiWidth, guiHeight);
            
        }
            
        /* Destructor*/
        ~Gui() {}

        /* Set size */
        void resized() override {

            leeGrid.setBounds(getLocalBounds());

        }

    private :
        
        Plugin&                         pluginReference;
        AudioProcessorValueTreeState&   valueTreeStateReference;
        LeeGrid                         leeGrid;
        const int                       guiWidth  { 400 };
        const int                       guiHeight { 400 };
        
};

/* Create Plugin */
AudioProcessorEditor*   Plugin::createEditor()              { return new Gui(*this, valueTreeState); }
AudioProcessor*         JUCE_CALLTYPE createPluginFilter()  { return new Plugin(); }