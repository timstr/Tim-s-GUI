#pragma once

#include <GUI/Element.hpp>
#include <GUI/Color.hpp>
#include <GUI/Text.hpp>

#include <memory>
#include <optional>
#include <variant>
#include <vector>

namespace ui {
    
    class Container : virtual public Element {
    public:
        Container();

        void render(sf::RenderWindow&) override;

    protected:

        template<typename T, typename... Args>
        T& add(Args&&...);

        void adopt(std::unique_ptr<Element>);

        std::unique_ptr<Element> release(const Element*);

        std::vector<Element*> children();
        std::vector<const Element*> children() const;

        // The available size is the space an element is allowed to fill
        void setAvailableSize(const Element* child, vec2 size);
        void unsetAvailableSize(const Element* child);
        std::optional<vec2> getAvailableSize(const Element* child) const;

        // Call this after computing the layout
        void updatePreviousSizes();
        vec2 getPreviousSize(const Element* child) const;

    private:

        Container* toContainer() override;

        Element* findElementAt(vec2 p) override;

        struct ChildData {
            std::unique_ptr<Element> child;
            std::optional<vec2> availableSize;
            vec2 previousSize;
        };

        std::vector<ChildData> m_children;

        Window* m_parentWindow;

        Window* getWindow() const override final;

        friend class Element;
        friend class Window;
    };

    // Template definitions

    template<typename T, typename... Args>
    inline T& Container::add(Args&&... args){
        static_assert(std::is_base_of_v<Element, T>, "T must derive from Element");
        auto c = std::make_unique<T>(std::forward<Args>(args)...);
        T& ret = *c;
        this->adopt(std::move(c));
        this->requireDeepUpdate();
        return ret;
    }

} // namespace ui