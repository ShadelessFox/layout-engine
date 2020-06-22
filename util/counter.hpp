#pragma once

class Counter {
public:
    Counter(double updateRate);

    void tick() noexcept;

    double value() const noexcept;

    double delta() const noexcept;

private:
    double _updateRate;
    double _delta { 0.0 };
    double _updateDelta { 0.0 };
    double _fps { 0.0 };
    unsigned int _prevFrameTime { 0 };
    unsigned int _lastFrameTime { 0 };
    unsigned int _totalFrames { 0 };
};