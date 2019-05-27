#include <GUI/Container.hpp>

#include <algorithm>

namespace ui {
    
    void Container::adopt(std::unique_ptr<Element> e){
        e->m_parent = this;
        auto eptr = e.get();
        m_children.push_back(std::move(e));
        require_update();
    }

    std::unique_ptr<Element> Container::release(const Element* e){
        auto match = [e](const auto& p){ return p.get() == e; };
        auto it = std::find_if(m_children.begin(), m_children.end(), match);
        if (it == m_children.end()){
            throw std::runtime_error("Attempted to remove a nonexistent child window");
        }
        std::unique_ptr<Element> ret = std::move(*it);
        m_children.erase(it);
        require_update();
        return ret;
    }

    std::vector<std::unique_ptr<Element>>& Container::children(){
        return m_children;
    }

    const std::vector<std::unique_ptr<Element>>& Container::children() const {
        return m_children;
    }

    void Container::render(sf::RenderWindow& rw){
        const auto old_view = rw.getView();
        // TODO: handle clipping here
        for (const auto& c : m_children){
            auto child_view = old_view;
            auto pos = c->pos();
            child_view.move(-pos);
            rw.setView(child_view);
            c->render(rw);
        }
        rw.setView(old_view);
    }

    Container* Container::toContainer(){
        return static_cast<Container*>(this);
    }
    

} // namespace ui
