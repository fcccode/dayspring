// This file is distributed under the BSD License.
// See "license.txt" for details.
// Copyright 2009-2012, Jonathan Turner (jonathan@emptycrate.com)
// Copyright 2009-2015, Jason Turner (jason@emptycrate.com)
// http://www.chaiscript.com

#ifndef CHAISCRIPT_HANDLE_RETURN_HPP_
#define CHAISCRIPT_HANDLE_RETURN_HPP_

#include <functional>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "boxed_number.hpp"
#include "boxed_value.hpp"
#include "type_info.hpp"

namespace chaiscript {
class Boxed_Number;
}  // namespace chaiscript

namespace chaiscript
{
  namespace dispatch
  {
    namespace detail
    {
      /**
       * Used internally for handling a return value from a Proxy_Function call
       */
      template<typename Ret>
        struct Handle_Return
        {
          static Boxed_Value handle(const Ret &r)
          {
            return const_var(r);
          }

          static Boxed_Value handle(Ret &&r)
          {
            return Boxed_Value(std::move(r));
          }
        };

      template<typename Ret>
        struct Handle_Return<Ret *>
        {
          static Boxed_Value handle(Ret *p)
          {
            return Boxed_Value(p);
          }
        };

      template<typename Ret>
        struct Handle_Return<const Ret *>
        {
          static Boxed_Value handle(const Ret *p)
          {
            return Boxed_Value(p);
          }
        };

      template<typename Ret>
        struct Handle_Return<std::shared_ptr<Ret> &>
        {
          static Boxed_Value handle(const std::shared_ptr<Ret> &r)
          {
            return Boxed_Value(r);
          }
        };

      template<typename Ret>
        struct Handle_Return<std::shared_ptr<Ret> >
        {
          static Boxed_Value handle(const std::shared_ptr<Ret> &r)
          {
            return Boxed_Value(r);
          }
        };

      template<typename Ret>
        struct Handle_Return<const std::shared_ptr<Ret> &>
        {
          static Boxed_Value handle(const std::shared_ptr<Ret> &r)
          {
            return Boxed_Value(r);
          }
        };

      template<typename Ret>
        struct Handle_Return<const Ret &>
        {
          static Boxed_Value handle(const Ret &r)
          {
            return Boxed_Value(std::cref(r));
          }
        };


      /**
       * Used internally for handling a return value from a Proxy_Function call
       */
      template<typename Ret>
        struct Handle_Return<Ret &>
        {
          static Boxed_Value handle(Ret &r)
          {
            return Boxed_Value(std::ref(r));
          }

          static Boxed_Value handle(const Ret &r)
          {
            return Boxed_Value(std::cref(r));
          }
        };

      /**
       * Used internally for handling a return value from a Proxy_Function call
       */
      template<>
        struct Handle_Return<Boxed_Value>
        {
          static Boxed_Value handle(const Boxed_Value &r)
          {
            return r;
          }
        };

      /**
       * Used internally for handling a return value from a Proxy_Function call
       */
      template<>
        struct Handle_Return<const Boxed_Value>
        {
          static Boxed_Value handle(const Boxed_Value &r)
          {
            return r;
          }
        };

      /**
       * Used internally for handling a return value from a Proxy_Function call
       */
      template<>
        struct Handle_Return<Boxed_Value &>
        {
          static Boxed_Value handle(const Boxed_Value &r)
          {
            return r;
          }
        };

      /**
       * Used internally for handling a return value from a Proxy_Function call
       */
      template<>
        struct Handle_Return<const Boxed_Value &>
        {
          static Boxed_Value handle(const Boxed_Value &r)
          {
            return r;
          }
        };

      /**
       * Used internally for handling a return value from a Proxy_Function call
       */
      template<>
        struct Handle_Return<Boxed_Number>
        {
          static Boxed_Value handle(const Boxed_Number &r)
          {
            return r.bv;
          }
        };

      /**
       * Used internally for handling a return value from a Proxy_Function call
       */
      template<>
        struct Handle_Return<const Boxed_Number>
        {
          static Boxed_Value handle(const Boxed_Number &r)
          {
            return r.bv;
          }
        };


      /**
       * Used internally for handling a return value from a Proxy_Function call
       */
      template<>
        struct Handle_Return<void>
        {
          static Boxed_Value handle()
          {
            return Boxed_Value(Boxed_Value::Void_Type());
          }
        };
    }
  }
}

#endif
