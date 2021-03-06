#pragma once

#include <OFC/DOM/Element.hpp>
#include <OFC/Util/Color.hpp>

#include <memory>
#include <optional>
#include <variant>
#include <vector>

namespace ofc::ui {

    class Window;

} // namespace ofc::ui

namespace ofc::ui::dom {
    
    class Container : virtual public Element {
    public:
        Container();
        ~Container();

        void render(sf::RenderWindow&) override;

        bool clipping() const;
        void setClipping(bool enabled);

        bool shrink() const;
        void setShrink(bool enable);

        bool empty() const;

        std::size_t numChildren() const;

        Element* getChild(std::size_t);
        const Element* getChild(std::size_t) const;

        bool hasChild(const Element*) const;
        bool hasDescendent(const Element*) const;

        std::vector<const Element*> children() const;

        void clear();

    protected:
        void adopt(std::unique_ptr<Element>);

        std::unique_ptr<Element> release(const Element*);

        virtual void onRemoveChild(const Element*);

        std::vector<Element*> children();

        // TODO: scale?

        // The available size is the space an element is allowed to fill
        void setAvailableSize(const Element* child, vec2 size);
        void unsetAvailableSize(const Element* child);
        std::optional<vec2> getAvailableSize(const Element* child) const;

        vec2 getRequiredSize(const Element* child) const;

    private:

        Container* toContainer() override;

        Element* findElementAt(vec2 p, const Element* exclude) override;

        struct ChildData {
            std::unique_ptr<Element> child;
            std::optional<vec2> availableSize;
            std::optional<vec2> previousSize;
            std::optional<vec2> requiredSize;
            std::optional<vec2> previousPos;
        };

        std::vector<ChildData> m_children;

        Window* m_parentWindow;

        bool m_clipping;
        bool m_shrink;

        Window* getWindow() const override final;
        
        // Call this after computing the layout
        void updatePreviousSizes(const Element* which = nullptr);
        std::optional<vec2> getPreviousSize(const Element* child) const;

        void setRequiredSize(const Element* child, vec2 size);

        friend class Element;

        friend class ::ofc::ui::Window;
        friend class ::ofc::ui::Root;
    };

} // namespace ofc::ui::dom
