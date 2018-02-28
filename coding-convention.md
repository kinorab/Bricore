# Breakout Brick(BB) Coding Conventions
This document is meant to serve as a guide to writing C++ in the BB codebase, covering when and how to use various language features as well as how code should be formatted. Our goal is to ensure a **consistently** high-quality codebase that is easy to read and contribute to, especially for newcomers.

The BB codebase contains a wide variety of code from many different authors. It's been through a few different major stages in its life. As a result, large (primarily older) parts of the codebase do not fit this guide. When in doubt about how to write or format something, always prefer the advice here over existing conventions in the code. **If you're already touching some older code as part of your work, please do clean it up as you go along. But please do not spend hours applying the formatting guidelines here to code you aren't otherwise modifying.** While we'd love for the entire codebase to follow this guide, we'd rather get there gradually than lose lots of git history and developer time to purely cosmetic changes. That said, if cosmetic changes that you're making as part of a larger
diff keep growing in scope, it may be worth pulling them out into a separate diff.

There's no well-defined cutoff here - just try to minimize effort for your reviewers. A good rule of thumb is that if your cosmetic changes require adding significant new sections to the diff (such as a function rename that touches
all callsites), it should probably be pulled out into its own diff.

## When to use references vs pointers

1. > Use reference wherever you can, pointers wherever you must.
Avoid pointers until you can't.
The reason is that pointers make things harder to follow/read, less safe and
far more dangerous manipulations than any other constructs.
   >
   > -- <cite>[an answer from "When to use references vs. pointers"](https://stackoverflow.com/a/7058373)</cite>

2. Prefer smart pointers to raw pointers when allocating objects.

   [What is a smart pointer and when should I use one?](https://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one)

   [What is the best smart pointer return type for a factory function?
](https://stackoverflow.com/questions/28294620/what-is-the-best-smart-pointer-return-type-for-a-factory-function)
3. But use raw pointers for reference semantics.

   [Smart Pointer Parameters](https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/)

   >You may be wondering why I am using raw pointers here, when everybody keeps telling that raw pointers are bad, unsafe, and dangerous. Actually, that is a precious warning, but it is important to put it in the correct context: **raw pointers are bad when used for performing manual memory management, i.e. allocating and deallocating objects through new and delete. When used purely as a means to achieve reference semantics and pass around non-owning, observing pointers, there is nothing intrinsically dangerous in raw pointers**, except maybe for the fact that one should take care not to dereference a dangling pointer.
   >
   > -- <cite>an [answer](https://stackoverflow.com/a/15649077) from [Using smart pointers for class members](https://stackoverflow.com/q/15648844)</cite>

## Const Correctness

> A good thing. It means using the keyword const to prevent const objects from getting mutated.
For example, if you wanted to create a function f() that accepted a std\:\:string, plus you want to promise callers not to change the caller¡¦s std::string that gets passed to f(), you can have f() receive its std::string parameter¡K
>
> -- <cite>[What is ¡§const correctness¡¨?](https://isocpp.org/wiki/faq/const-correctness#overview-const)</cite>

## Getter, Setter and Public Member

In short: (Logic inside object) >> Getter, Setter > Public Member

### When are Getters and Setters Justified?

> Having getters and setters does not in itself break encapsulation.
What does break encapsulation is having a getter and a setter for every data member.
That is one step away from making all data members public.
 >
 > -- <cite>an [answer](https://softwareengineering.stackexchange.com/a/21809) from [When are Getters and Setters Justified](https://softwareengineering.stackexchange.com/q/21802)</cite>

Still, the example provided in the answer didn't get it all right, as mentioned in its highest scored comment:
> The example has it all wrong. There should not be an Age field nor a setAge() method. Age is a function of the Person birthDate as compared to some point in time. While seemingly trivial, this is exactly what is wrong with the modern practice of full mutability of objects and other bad designs, as seen by get/set methods for private fields versus carefully considering what is really mutable, what is a field, what the object should know about its behaviors and what state changes are actually valid (which setX methods completely destroy).

[Tell, don't ask.](https://martinfowler.com/bliki/TellDontAsk.html)

<img src="https://i.imgur.com/msUlC0j.png" alt="Put the logic inside object" style="width: 400px;"/>

[Why getter and setter methods are evil](https://www.javaworld.com/article/2073723/core-java/why-getter-and-setter-methods-are-evil.html)

[Getter¡BSetter use or not(chinese)](https://www.ithome.com.tw/voice/98804)

[GETTERS AND SETTERS ARE NOT EVIL](https://techblog.bozho.net/getters-and-setters-are-not-evil/)

[Getters/Setters. Evil. Period.](https://www.yegor256.com/2014/09/16/getters-and-setters-are-evil.html)

## "this" Pointer

Omit "this" pointer whenever possible.

## Hiding class implementation

Prefer interface over PIMPL idiom.

<img src="https://i.imgur.com/1epMgld.png" alt="interface example" style="width: 400px;"/>

## Prefer composition over inheritance

> -- <cite>an [answer](https://softwareengineering.stackexchange.com/a/134115) from [Why should I prefer composition over inheritance?](https://softwareengineering.stackexchange.com/q/134097)</cite>

## Use "override" and "final" specifiers

## A method should do one thing and only one thing

Good clues your method is doing more than one thing:

* More than one level of indention in a method : indicates too many logic branches to only be doing one thing

* "Paragraph Breaks" : whitespace between logical groups of code indicate the method is doing more than one thing

* Too many lines : "Lines of code" is a bad metric for pretty much anything. It is only a helpful indicator that can potentially point to the real issue. If you have to justify with some number or something, figure out the maximum number of lines that fit on a typical development editor window at your shop, and use that.

## Write Short Functions
> Prefer small and focused functions.
>
>We recognize that long functions are sometimes appropriate, so no hard limit is placed on functions length. If a function exceeds about 40 lines, think about whether it can be broken up without harming the structure of the program.
>
>Even if your long function works perfectly now, someone modifying it in a few months may add new behavior. This could result in bugs that are hard to find. Keeping your functions short and simple makes it easier for other people to read and modify your code.
>
>You could find long and complicated functions when working with some code. Do not be intimidated by modifying existing code: if working with such a function proves to be difficult, you find that errors are hard to debug, or you want to use a piece of it in several different contexts, consider breaking up the function into smaller and more manageable pieces.
>
> -- <cite>[Write Short Functions](https://google.github.io/styleguide/cppguide.html#Write_Short_Functions) in Google C++ Style Guide</cite>

## Forward-Declaration

Use forward-declaration instead of #include, if possible.
>There are no downsides to forward-declaring classes, but I can think of some downsides for including headers unnecessarily:
>
>longer compilation time, since all translation units including C.h will also include A.h, although they might not need it.
>
>possibly including other headers you don't need indirectly
>
>polluting the translation unit with symbols you don't need
>
>you might need to recompile source files that include that header if it changes (@PeterWood)
>
>-- <cite>an [answer](https://stackoverflow.com/a/9906429) from[Should one use forward declarations instead of includes wherever possible?](https://stackoverflow.com/q/9906402)</cite>

## Import and Export Resources

[How to: Import and Export Resources](https://msdn.microsoft.com/en-us/library/saced6x2.aspx)

## Resources

[Google Style Guide](https://google.github.io/styleguide/cppguide.html)