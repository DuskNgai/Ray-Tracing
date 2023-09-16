#ifndef _RAY_TRACING_MATERIAL_MATERIAL_RECORD_HPP_
#define _RAY_TRACING_MATERIAL_MATERIAL_RECORD_HPP_

#include <memory>

#include <pdf/base-pdf.hpp>
#include <ray.hpp>

RAY_TRACING_NAMESPACE_BEGIN

struct MaterialRecord {
    Color3f attenuation;
    std::shared_ptr<PDF> pdf_ptr;
    Ray specular_ray;
    bool is_specular;
};

RAY_TRACING_NAMESPACE_END

#endif // !_RAY_TRACING_MATERIAL_MATERIAL_RECORD_HPP_
