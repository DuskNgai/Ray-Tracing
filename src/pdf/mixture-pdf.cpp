#include <pdf/mixture-pdf.hpp>

RAY_TRACING_NAMESPACE_BEGIN

MixturePDF::MixturePDF(std::shared_ptr<PDF> const& pdf0, std::shared_ptr<PDF> const& pdf1)
    : pdf0(pdf0)
    , pdf1(pdf1) {}

Float MixturePDF::value(Vector3f const& direction) const {
    return 0.5_f * this->pdf0->value(direction) + 0.5_f * this->pdf1->value(direction);
}

Vector3f MixturePDF::generate(RandomNumberGenerator& rng) const {
    if (rng() < 0.5_f) {
        return this->pdf0->generate(rng);
    }
    else {
        return this->pdf1->generate(rng);
    }
}

RAY_TRACING_NAMESPACE_END
