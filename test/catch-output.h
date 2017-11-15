#include <iostream>
#include <DirectXMath.h>

namespace DirectX {

inline std::ostream& operator<<(std::ostream& os, XMMATRIX const& value)
{
    float const(*const pValue)[4] = (float(*)[4]) & value;
    os << "{ " << pValue[0][0] << ", " << pValue[0][1] << ", " << pValue[0][2] << ", "
       << pValue[0][3] << " }\n";
    os << "{ " << pValue[1][0] << ", " << pValue[1][1] << ", " << pValue[1][2] << ", "
       << pValue[1][3] << " }\n";
    os << "{ " << pValue[2][0] << ", " << pValue[2][1] << ", " << pValue[2][2] << ", "
       << pValue[2][3] << " }\n";
    os << "{ " << pValue[3][0] << ", " << pValue[3][1] << ", " << pValue[3][2] << ", "
       << pValue[3][3] << " }";
    return os;
}

inline std::ostream& operator<<(std::ostream& os, XMVECTOR const& value)
{
    os << "{ " << XMVectorGetX(value) << ", " << XMVectorGetY(value) << ", " << XMVectorGetZ(value)
       << ", " << XMVectorGetW(value) << " }";
    return os;
}

}  // namespace DirectX

#include <glm/glm.hpp>

namespace glm {

inline std::ostream& operator<<(std::ostream& os, glm::mat3 const& value)
{
    os << "{ " << value[0][0] << ", " << value[0][1] << ", " << value[0][2] << " }\n";
    os << "{ " << value[1][0] << ", " << value[1][1] << ", " << value[1][2] << " }\n";
    os << "{ " << value[2][0] << ", " << value[2][1] << ", " << value[2][2] << " }";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, glm::vec3 const& value)
{
    os << "{ " << value[0] << ", " << value[1] << ", " << value[2] << " }";
    return os;
}

}  // namespace glm

#include "akmath.h"

namespace ak {

inline std::ostream& operator<<(std::ostream& os, ak::Mat3 const& value)
{
    os << "{ " << value.c0.x << ", " << value.c0.y << ", " << value.c0.z << " }\n";
    os << "{ " << value.c1.x << ", " << value.c1.y << ", " << value.c1.z << " }\n";
    os << "{ " << value.c2.x << ", " << value.c2.y << ", " << value.c2.z << " }";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ak::Mat4 const& value)
{
    os << "{ " << value.c0.x << ", " << value.c0.y << ", " << value.c0.z << ", " << value.c0.w
       << " }\n";
    os << "{ " << value.c1.x << ", " << value.c1.y << ", " << value.c1.z << ", " << value.c1.w
       << " }\n";
    os << "{ " << value.c2.x << ", " << value.c2.y << ", " << value.c2.z << ", " << value.c2.w
       << " }\n";
    os << "{ " << value.c3.x << ", " << value.c3.y << ", " << value.c3.z << ", " << value.c3.w
       << " }";
    return os;
}
inline std::ostream& operator<<(std::ostream& os, ak::Vec3 const& value)
{
    os << "{ " << value.x << ", " << value.y << ", " << value.z << " }";
    return os;
}

}  // namespace ak
