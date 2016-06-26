/**
 *  stack_ptr.h
 *
 *  Implementation of an object that behaves like a
 *  smart pointer but is actually managed on the stack
 *
 *  @copyright 2016 Copernica B.V.
 */

/**
 *  Dependencies
 */
#include <type_traits>
#include <utility>

/**
 *  Set up namespace
 */
namespace AMQP {

/**
 *  Stack-based smart pointer
 */
template <typename T>
class stack_ptr
{
private:
    /**
     *  Storage for the object
     *  @var    std::aligned_storage<sizeof(T), alignof(T)>
     */
    typedef typename std::aligned_storage<sizeof(T), alignof(T)>::type Type;
    Type _data;

    /**
     *  Is the pointer initialized?
     *  @var    boolean
     */
    bool _initialized;
public:
    /**
     *  Constructor
     */
    stack_ptr() : _initialized(false) METHOD_DEFAULT;

    /**
     *  Copy and moving is disabled
     *
     *  @param  that    The stack_ptr we refuse to copy/move
     */
    stack_ptr(const stack_ptr &that) METHOD_DELETE;
    stack_ptr(stack_ptr &&that) METHOD_DELETE;

    /**
     *  Destructor
     */
    ~stack_ptr()
    {
        // reset the pointer
        reset();
    }

    /**
     *  Reset the pointer
     */
    void reset()
    {
        // are we initialized?
        if (!_initialized) return;

        // destroy the object
        reinterpret_cast<T*>(&_data)->~T();

        // the object is not currently initialized
        _initialized = false;
    }

    /**
     *  Construct the object
     *
     *  @param  ...     Zero or more constructor arguments for T
     */
    template <typename Arg1>
    void construct(Arg1&& parameter1)
    {
        // first reset the current object
        reset();

        // initialize new object
        new (&_data) T(parameter1);
        _initialized = true;
    }

    template <typename Arg1, typename Arg2>
    void construct(Arg1&& parameter1, Arg2&& parameter2)
    {
        // first reset the current object
        reset();

        // initialize new object
        new (&_data) T(parameter1, parameter2);
        _initialized = true;
    }

    /**
     *  Is the object initialized?
     *
     *  @return Are we currently managing an object?
     */
    operator bool() const
    {
        // are we initialized with an object?
        return _initialized;
    }

    /**
     *  Retrieve a pointer to the object
     *
     *  @return Pointer to the object or nullptr if no object is managed
     */
    T *get() const
    {
        // do we have a managed object
        if (!_initialized) return nullptr;

        // return pointer to the managed object
        return const_cast<T*>(reinterpret_cast<const T*>(&_data));
    }

    /**
     *  Retrieve a reference to the object
     *
     *  @return Reference to the object, undefined if no object is managed
     */
    T &operator*() const
    {
        // dereference the pointer
        return *operator->();
    }

    /**
     *  Retrieve a pointer to the object
     *
     *  @return Pointer to the object, undefined if no object is managed
     */
    T *operator->() const
    {
        // return pointer to the managed object
        return const_cast<T*>(reinterpret_cast<const T*>(&_data));
    }
};

/**
 *  End namespace
 */
}
