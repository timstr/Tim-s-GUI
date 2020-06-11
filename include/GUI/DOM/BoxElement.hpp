#pragma once

#include <GUI/DOM/Element.hpp>
#include <GUI/Util/RoundedRectangle.hpp>
#include <GUI/Util/Color.hpp>

namespace ui::dom {
    
    class BoxElement : virtual public Element {
    public:
        BoxElement();

        Color borderColor() const;
        Color backgroundColor() const;

        void setBorderColor(const Color&);
        void setBackgroundColor(const Color&);

        float borderRadius() const;
        float borderThickness() const;

        void setBorderRadius(float);
        void setBorderThickness(float);

        void render(sf::RenderWindow&) override;

        void onResize() override;

    private:
        RoundedRectangle m_rect;
    };

    // Convenient template for mixing BoxElement with any container
    template<typename ContainerType>
    class Boxed : public ContainerType, public BoxElement {
    public:
        static_assert(std::is_base_of_v<Container, ContainerType>, "ContainerType must derive from Container");

        using ContainerType::ContainerType;

        void render(sf::RenderWindow& rw) override {
            BoxElement::render(rw);
            ContainerType::render(rw);
        }
    };

} // namespace ui::dom