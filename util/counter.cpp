#include "counter.hpp"

#include <SDL2/SDL.h>

Counter::Counter(double updateRate)
    : _updateRate(updateRate)
{
}

double Counter::delta() const noexcept
{
    return _delta;
}

double Counter::value() const noexcept
{
    return _fps;
}

void Counter::tick() noexcept
{
    _totalFrames++;

    _lastFrameTime = SDL_GetTicks();
    _delta = (_lastFrameTime - _prevFrameTime) / 1000.0;
    _updateDelta += _delta;
    _prevFrameTime = _lastFrameTime;

    if (_updateDelta > _updateRate) {
        _fps = _totalFrames / _updateDelta;
        _totalFrames = 0;
        _updateDelta -= _updateRate;
    }
}