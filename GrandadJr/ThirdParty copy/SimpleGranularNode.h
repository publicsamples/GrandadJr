#pragma once

#include <JuceHeader.h>
#include <vector>
#include <cmath>

namespace scriptnode
{

// Utility: create a Hann window
inline std::vector<float> makeHannWindow(int length)
{
    std::vector<float> w(length);
    for (int i = 0; i < length; i++)
        w[i] = 0.5f - 0.5f * std::cos(2.0 * juce::MathConstants<double>::pi * i / (length - 1));
    return w;
}

struct SimpleGranularNode : public hise::dsp::scriptnode
{
    struct Grain
    {
        int startSample = 0;   // where in source buffer
        int posInGrain = 0;    // current position inside grain
        int length = 0;        // length in samples
        float rate = 1.0f;     // playback rate (not used yet, only =1)
        float amp = 0.5f;      // amplitude
        std::vector<float> window;
    };

    juce::AudioBuffer<float> source;   // static source buffer
    std::vector<Grain> grains;
    double sampleRate = 44100.0;

    // Parameters
    float density = 10.0f;    // grains per second
    float grainSize = 0.1f;   // seconds
    float gain = 0.5f;        // overall gain

    juce::Random random;

    void prepare(PrepareSpecs specs)
    {
        sampleRate = specs.sampleRate;

        // For testing: fill source buffer with a sine wave
        int numSamples = (int)sampleRate; // 1 sec
        source.setSize(1, numSamples);
        for (int i = 0; i < numSamples; i++)
        {
            float s = std::sin(2.0 * juce::MathConstants<double>::pi * 220.0 * i / sampleRate);
            source.setSample(0, i, s);
        }
    }

    void process(ProcessData& data)
    {
        for (int i = 0; i < data.numSamples; i++)
        {
            // Grain spawning
            if (random.nextFloat() < density / (float)sampleRate)
                spawnGrain();

            float out = 0.0f;

            for (auto it = grains.begin(); it != grains.end(); )
            {
                int idx = it->startSample + it->posInGrain;

                if (idx >= source.getNumSamples())
                {
                    it = grains.erase(it);
                    continue;
                }

                float sample = source.getSample(0, idx);
                float env = it->window[it->posInGrain];
                out += sample * env * it->amp;

                it->posInGrain++;
                if (it->posInGrain >= it->length)
                    it = grains.erase(it);
                else
                    ++it;
            }

            out *= gain;

            for (int ch = 0; ch < data.numChannels; ch++)
                data.channels[ch][i] = out;
        }
    }

    void setParameter(int idx, float value) 
    {
        switch (idx)
        {
            case 0: gain = value; break;
            case 1: density = value; break;
            case 2: grainSize = value; break;
        }
    }

    void reset()
    
    {
        grains.clear();
    }

    void spawnGrain()
    {
        Grain g;
        g.length = (int)(grainSize * sampleRate);
        g.startSample = random.nextInt(source.getNumSamples() - g.length);
        g.posInGrain = 0;
        g.amp = 0.5f;
        g.rate = 1.0f;
        g.window = makeHannWindow(g.length);
        grains.push_back(g);
    }
};

REGISTER_PROCESSOR(SimpleGranularNode, "fx.simplegran");

} // namespace scriptnode
