#ifndef _RAY_TRACING_PDF_MIXTURE_PDF_HPP_
#define _RAY_TRACING_PDF_MIXTURE_PDF_HPP_

#include <pdf/base-pdf.hpp>

RAY_TRACING_NAMESPACE_BEGIN

class MixturePDF : public PDF {
private:
    std::shared_ptr<PDF> pdf0;
    std::shared_ptr<PDF> pdf1;

public:
    MixturePDF(const std::shared_ptr<PDF>& pdf0, const std::shared_ptr<PDF>& pdf1);

    virtual Float value(const Vector3f& direction) const override;

    virtual Vector3f generate(RandomNumberGenerator& rng) const override;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_PDF_MIXTURE_PDF_HPP_
