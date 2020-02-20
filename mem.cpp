#include <map>
#include <memory>
#include <functional>
#include <iostream>

class Signal
{
public:
    void set(std::function<void()> func) noexcept
    {
        m_func = func;
    }
    void del() noexcept
    {
        m_func = nullptr;
    }
    void call() const
    {
        if(m_func) m_func();
    }

private:
    std::function<void()> m_func;
};

class Object
{
public:
    Object() = default;
    Object(const std::string& name)
    {
        m_name = name;
    }
    ~Object() {std::cout << "Object Destructor" << std::endl; m_ptr.reset();}

    void ckick()
    {
        for(const auto& i : on_click)
        {
            i.second.call();
        }
    }

    std::string get_name() const noexcept
    {
        return m_name;
    }

private:
    void set_self_ptr(std::shared_ptr<Object> ptr)
    {
        if(ptr) m_ptr = ptr;
    }

public:
    std::map<std::string, Signal> on_click;

private:
    std::string m_name;
    std::shared_ptr<Object> m_ptr;
    template <typename T>
    friend T& create(const std::string& name);
};

template <typename T>
T& create(const std::string& name)
{
    auto obj = std::make_shared<T>(name);
    obj->set_self_ptr(obj);
    return *obj;
}



// auto btn = create<Object>("Hello") (txt.setText("Hello");); //btn is a wrapper for shared_ptr

// btn.on_click["set_text"] { txt.set_text("Hello"); };           //mem_func { txt.setText("Hello"); };
// btn.off_click["set_text"];

int main()
{
    auto btn = create<Object>("Hello");

    btn.on_click["set_text"].set([](){std::cout << "Hello" << std::endl;});
    btn.ckick();
    btn.on_click["set_text"].del();
    btn.ckick();
}
