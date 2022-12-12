A text-based learning robot that tries to get to know its users. It runs on a Raspberry Pi and Windows.

I've been working on this chatbot on and off for about 20 years, and while I've made a lot of progress, there's a great deal of work left to do.

I wanted to make a chatbot that is better than the AIML types that are so common. Something that would pay attention to who it was talking to and try to learn from that person. It would not guess at an answer when it has no understanding of what was said.

Note: There's more info in the wiki.

## About this program
* It will try to make sense of every word in a sentence. It will never pretend to know its meaning. It will attempt to explain what it's having trouble with. The user may be able to explain new words that are new to it.
* Its database relies on a classification of basic knowledge
* It uses templates to interpret sentences
* Only certain types of words are allowed to fit in the templates
* It starts out with simple features and is expandable
* ID numbers are used identify specific members of a category, usually people could also be pets, buildings database entries start with a number sign followed by the id number* Will expect to know who it's talking to
* Will remember elements of conversations
* Will try to use people to expand it's knowledge
* The source code is documented so that even non-programmers should be able to figure out what's goin on.

For statements, a function is called based on the verb used. The information provided is stored in the database. The bot will ask about anything that is unfamiliar to it. It will point out contradictory info when nessessary

For questions, a function is called based on the verb used. The information requested is retrieved from the database

## How it works


## Current limitations
* Only full sentences
* No pronouns, adjectives or adverbs
* No figures of speech
* No slang
* No compound sentences (example: "Hi, how are you")
* Ignores multiple meanings 

## Programming details
* Language: C
* Editor: Code::Blocks
* Compiler: GCC
* Platform: Raspberry Pi with Raspian and Windows

## Long term goals
* Will form opinions of the people it talks to
* Will initiate conversation if the user doesn't
* Will be thinking of various things when it's not in a conversation. This activity may have an effect on its mood, may cause it to arrive at some conclusions. It may be prompted to ask related questions. It can be asked "what are you thinking about".

