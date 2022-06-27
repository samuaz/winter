//
// Created by samuaz on 3/5/21.
//

#ifndef WINTERCPP_WINTER_SINGLETON_TEMPLATE_H
#define WINTERCPP_WINTER_SINGLETON_TEMPLATE_H
#define WINTER_SINGLETON(_CLASSNAME_)                                        \
   public:                                                                   \
    static auto &instance() {                                                \
        return *_instance;                                                   \
    }                                                                        \
    static auto &init() {                                                    \
        std::call_once(_m_once, [&]() {                                      \
            std::cout << "starting: " << typeid(_CLASSNAME_).name() << "\n"; \
            _instance.reset(new _CLASSNAME_());                              \
        });                                                                  \
        return *_instance;                                                   \
    };                                                                       \
    _CLASSNAME_(_CLASSNAME_ const &) = delete;                               \
    _CLASSNAME_ &operator=(const _CLASSNAME_ &) = delete;                    \
    _CLASSNAME_(_CLASSNAME_ &&) = delete;                                    \
    _CLASSNAME_ &operator=(_CLASSNAME_ &&) = delete;                         \
                                                                             \
   private:                                                                  \
    _CLASSNAME_() = default;                                                 \
    static inline std::unique_ptr<_CLASSNAME_> _instance;                    \
    static inline std::once_flag _m_once;
#endif  // WINTERCPP_WINTER_SINGLETON_TEMPLATE_H
