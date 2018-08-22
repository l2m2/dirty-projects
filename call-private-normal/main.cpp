/// Ref:
/// http://bloglitb.blogspot.com/2010/07/access-to-private-members-thats-easy.html

#include <iostream>

template<typename Tag>
struct result {
    /* export it ... */
    typedef typename Tag::type type;
    static type ptr;
};
template<typename Tag>
typename result<Tag>::type result<Tag>::ptr;
template<typename Tag, typename Tag::type p>
struct rob : result<Tag> {
    /* fill it ... */
    struct filler {
        filler() { result<Tag>::ptr = p; }
    };
    static filler filler_obj;
};
template<typename Tag, typename Tag::type p>
typename rob<Tag, p>::filler rob<Tag, p>::filler_obj;

class A {
private:
    void func() {
        std::cout << __func__ << std::endl;
    }
    void func2(int n) {
        std::cout << __func__ << n << std::endl;
    }
};

struct Af { typedef void(A::*type)(); };
template class rob<Af, &A::func>;

struct Af2 { typedef void(A::*type)(int); };
template class rob<Af2, &A::func2>;

int main()
{
    A a;
    (a.*result<Af>::ptr)();
    (a.*result<Af2>::ptr)(4);
    return 0;
}
