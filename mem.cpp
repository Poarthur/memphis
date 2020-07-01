#include <map>
#include <memory>
#include <functional>
#include <iostream>
#include <atomic>

class Event
{
    //TODO after prt task
};

class Signal
{
    using Funcion = std::function<void()>;
public:
    void operator=(const Funcion& func) noexcept      //TODO Template for rvalue
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
    Funcion m_func;
};

class Object
{
public:
    static auto create(const std::string& name = "")
    {
        //return name.empty ? std::make_shared<Object>() : std::make_shared<Object>(name);
        return name.empty() ? std::shared_ptr<Object>(new Object()) : std::shared_ptr<Object>(new Object(name));
    }

    virtual ~Object()
    {
        std::cout << "Object Destructor" << std::endl;
    }

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
    Object() = default;
    Object(const std::string& name)
    {
        m_name = name;
    }

public:
    std::map<std::string, Signal> on_click;

private:
    std::string m_name;
};



// auto btn = create<Object>("Hello") (txt.setText("Hello");); //btn is a wrapper for shared_ptr

// btn.on_click["set_text"] { txt.set_text("Hello"); };           //mem_func { txt.setText("Hello"); };
// btn.off_click["set_text"];

int main()
{
    auto btn = Object::create("Hello");     //Object::set_child
    int tmp = 12;
    btn->on_click["set_text"] = [&tmp](){tmp++; std::cout << "Hello" << std::endl;};
    btn->ckick();
    btn->on_click["set_text"].del();
    btn->ckick();
}
