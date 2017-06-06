
#pragma once


#include <cstdint>
#include <string>

#include <glm/fwd.hpp>

#include <gloperate/gloperate_api.h>


namespace gloperate
{


/**
*  @brief
*    A four component ubyte color class (red, green, blue and alpha).
*
*    Internally, the components are stored in the format BGRA to be complient to the Qt QColor.
*/
class GLOPERATE_API Color
{
public:
    using vector_type = glm::tvec4<unsigned char, glm::highp>;


public:
    /**
    *  @brief
    *    Constructor
    *
    *    Constructs a Color with all components '0'
    */
    Color();

    /**
    *  @brief
    *    Constructor
    *
    *    Constructs a color with given component values
    *
    *  @param[in] bgra
    *    The component values
    */
    explicit Color(std::uint32_t bgra);

    /**
    *  @brief
    *    Constructor
    *
    *    Constructs a color with given component values
    *
    *  @param[in] red
    *    The red component value [0..255]
    *  @param[in] green
    *    The green component value [0..255]
    *  @param[in] blue
    *    The blue component value [0..255]
    *  @param[in] alpha
    *    The alpha component value [0..255] (optional)
    */
    Color(int red, int green, int blue, int alpha = 255);

    /**
    *  @brief
    *    Constructor
    *
    *    Constructs a color with given component values
    *
    *  @param[in] red
    *    The red component value [0..1]
    *  @param[in] green
    *    The green component value [0..1]
    *  @param[in] blue
    *    The blue component value [0..1]
    *  @param[in] alpha
    *    The alpha component value [0..1] (optional)
    */
    Color(float red, float green, float blue, float alpha = 1.0f);

    /**
    *  @brief
    *    Constructor
    *
    *    Constructs a color with given component values
    *
    *  @param[in] bgra
    *    The component values
    */
    Color(const vector_type & bgra);

    /**
    *  @brief
    *    Compare for equality
    *
    *  @param[in] rhs
    *    The other color
    *
    *  @return
    *    'true' if all component values are equal, else 'false'
    */
    bool operator==(const Color & rhs) const;

    /**
    *  @brief
    *    Compare for inequality
    *
    *  @param[in] rhs
    *    The other color
    *
    *  @return
    *    'true' if any component values differs, else 'false'
    */
    bool operator!=(const Color & rhs) const;

    /**
    *  @brief
    *    Get the component values as unsigned int
    *
    *  @return
    *    An unsigned int representation of the color
    */
    unsigned int bgra() const;

    /**
    *   @brief
    *     Update all component values
    *
    *   @param[in] bgra
    *     The component values
    */
    void setBgra(std::uint32_t bgra);

    /**
    *  @brief
    *    Get the red component value
    *
    *  @return
    *    The red component value [0..255]
    */
    unsigned char red() const;

    /**
    *  @brief
    *    Update the red component value
    *
    *  @param[in] value
    *    The red component value [0..255]
    */
    void setRed(unsigned char value);

    /**
    *  @brief
    *    Get the green component value
    *
    *  @return
    *    The green component value [0..255]
    */
    unsigned char green() const;

    /**
    *  @brief
    *    Update the green component value
    *
    *  @param[in] value
    *    The green component value [0..255]
    */
    void setGreen(unsigned char value);

    /**
    *  @brief
    *    Get the blue component value
    *
    *  @return
    *    The blue component value [0..255]
    */
    unsigned char blue() const;

    /**
    *  @brief
    *    Update the blue component value
    *
    *  @param[in] value
    *    The blue component value [0..255]
    */
    void setBlue(unsigned char value);

    /**
    *  @brief
    *    Get the alpha component value
    *
    *  @return
    *    The alpha component value [0..255]
    */
    unsigned char alpha() const;

    /**
    *  @brief
    *    Update the alpha component value
    *
    *  @param[in] value
    *    The alpha component value [0..255]
    */
    void setAlpha(unsigned char value);

    /**
    *  @brief
    *    Get the red component value as float
    *
    *  @return
    *    The red component value [0..1]
    */
    float redf() const;

    /**
    *  @brief
    *    Update the red component value as float
    *
    *  @param[in] value
    *    The red component value [0..1]
    */
    void setRedf(float value);

    /**
    *  @brief
    *    Get the green component value as float
    *
    *  @return
    *    The green component value [0..1]
    */
    float greenf() const;

    /**
    *  @brief
    *    Update the green component value as float
    *
    *  @param[in] value
    *    The green component value [0..1]
    */
    void setGreenf(float value);

    /**
    *  @brief
    *    Get the blue component value as float
    *
    *  @return
    *    The blue component value [0..1]
    */
    float bluef() const;

    /**
    *  @brief
    *    Update the blue component value as float
    *
    *  @param[in] value
    *    The blue component value [0..1]
    */
    void setBluef(float value);

    /**
    *  @brief
    *    Get the alpha component value as float
    *
    *  @return
    *    The alpha component value [0..1]
    */
    float alphaf() const;

    /**
    *  @brief
    *    Update the alpha component value as float
    *
    *  @param[in] value
    *    The alpha component value [0..1]
    */
    void setAlphaf(float value);

    /**
    *  @brief
    *    Convert color to glm::vec3
    *
    *  @return
    *    RGB float vector
    */
    glm::vec3 toVec3() const;

    /**
    *  @brief
    *    Convert color to glm::vec4
    *
    *  @return
    *    RGBA float vector
    */
    glm::vec4 toVec4() const;

    /**
    *  @brief
    *    Convert color to hex string
    *
    *  @return
    *    Hex representation (e.g., '#FFFFFFFF')
    */
    std::string toHexString() const;

    /**
    *  @brief
    *    Set color from hex string
    *
    *  @param[in] hex
    *    Hex representation (e.g., '#FFFFFFFF')
    *
    *  @return
    *    'true' if conversion was successful, else 'false'
    *
    *  @remarks
    *    The hex string must start with a '#' and must contain 3 or 4 components.
    */
    bool fromHexString(const std::string & hex);

    /**
    *  @brief
    *    Get mixed color
    *
    *  @param[in] other
    *    The color to mix with
    *  @param[in] interpolationValue
    *    Ratio of the colors [0..1] (0.0 for this color, 1.0 for other color)
    *
    *  @return
    *    The mixed color
    */
    Color interpolate(const Color & other, float interpolationValue) const;


protected:
    union
    {
        std::uint8_t  m_bgra[4]; ///< Per component representation of the color
        std::uint32_t m_v;       ///< GBRA representation of the color
    };
};


} // namespace gloperate
