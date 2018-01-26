# Projec1 Coding Conventions
This document is meant to serve as a guide to writing C++ in the Project1 codebase,
covering when and how to use various language features as well as how code should be formatted.
Our goal is to ensure a **consistently** high-quality codebase
that is easy to read and contribute to, especially for newcomers.

The Project1 codebase contains a wide variety of code from many different authors.
It's been through a few different major stages in its life, including stints in
multiple different repositories. As a result, large (primarily older) parts of
the codebase do not fit this guide. When in doubt about how to write or format
something, always prefer the advice here over existing conventions in the
code. **If you're already touching some older code as part of your work, please
do clean it up as you go along. But please do not spend hours applying the
formatting guidelines here to code you aren't otherwise modifying.** While we'd
love for the entire codebase to follow this guide, we'd rather get there
gradually than lose lots of git history and developer time to purely cosmetic
changes. That said, if cosmetic changes that you're making as part of a larger
diff keep growing in scope, it may be worth pulling them out into a separate
diff.

There's no well-defined cutoff here - just try to minimize effort for your
reviewers. A good rule of thumb is that if your cosmetic changes require adding
significant new sections to the diff (such as a function rename that touches
all callsites), it should probably be pulled out into its own diff.

## When to use references vs pointers

1. > Use reference wherever you can, pointers wherever you must.
Avoid pointers until you can't.
The reason is that pointers make things harder to follow/read, less safe and
far more dangerous manipulations than any other constructs.

   [when-to-use-references-vs-pointers](https://stackoverflow.com/questions/7058339/when-to-use-references-vs-pointers)

2. Prefer smart pointers to plain pointers.

   [what-is-a-smart-pointer-and-when-should-i-use-one](https://stackoverflow.com/questions/106508/what-is-a-smart-pointer-and-when-should-i-use-one)

   But use plain pointers in function parameters when needed.

   [Smart Pointer Parameters](https://herbsutter.com/2013/06/05/gotw-91-solution-smart-pointer-parameters/)

## Const Correctness

> A good thing. It means using the keyword const to prevent const objects from getting mutated.
For example, if you wanted to create a function f() that accepted a std\:\:string, plus you want to promise callers not to change the caller’s std::string that gets passed to f(), you can have f() receive its std::string parameter…

[What is “const correctness”?](https://isocpp.org/wiki/faq/const-correctness#overview-const)

## Getter, Setter and Public Member

In short: (Logic inside object) >> Getter, Setter > Public Member

### When are Getters and Setters Justified?

> Having getters and setters does not in itself break encapsulation.
What does break encapsulation is having a getter and a setter for every data member.
That is one step away from making all data members public.

--<cite>the highest scored answer from [When are Getters and Setters Justified](https://softwareengineering.stackexchange.com/questions/21802/when-are-getters-and-setters-justified)</cite>

Still, the example provided in the answer didn't get it all right, as mentioned in its highest scored comment:
> The example has it all wrong. There should not be an Age field nor a setAge() method. Age is a function of the Person birthDate as compared to some point in time. While seemingly trivial, this is exactly what is wrong with the modern practice of full mutability of objects and other bad designs, as seen by get/set methods for private fields versus carefully considering what is really mutable, what is a field, what the object should know about its behaviors and what state changes are actually valid (which setX methods completely destroy).

[Tell, don't ask.](https://martinfowler.com/bliki/TellDontAsk.html)

<img src="https://i.imgur.com/msUlC0j.png" alt="Put the logic inside object" style="width: 400px;"/>

[Why getter and setter methods are evil](https://www.javaworld.com/article/2073723/core-java/why-getter-and-setter-methods-are-evil.html)

[Getter、Setter的用與不用](https://www.ithome.com.tw/voice/98804)

[GETTERS AND SETTERS ARE NOT EVIL](https://techblog.bozho.net/getters-and-setters-are-not-evil/)

[Getters/Setters. Evil. Period.](https://www.yegor256.com/2014/09/16/getters-and-setters-are-evil.html)

## "this" Pointer

Omit "this" pointer whenever possible.