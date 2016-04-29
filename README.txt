Everything here works, with the exception of iof_chunk. It used to work and then I decided to start redesigning it and not finish.

This so called toolbox is the toolbox of code I use in all my projects; I've got something for most everything, and when I don't I make a tool for it. The goal is to reduce the code base of any new project.

I use the cheryl-engine to create rendered applications. I've got a thread-safe logger which is used to help diagnose the causes of bugs and glitches; which comes with a stack tracing snippet, which I found on the internet, that I fashioned into something useful to the logger and any project that might need *just* a stack tracer. There is even a relatively small header filled with bit twiddling template functions. That is the most important stuff.
