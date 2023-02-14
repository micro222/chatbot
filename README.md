A text-based learning robot that tries to get to know its users. It runs on a Raspberry Pi and Windows.

I've been working on this chatbot on and off for about 20 years, and while I've made a lot of progress, there's a great deal of work left to do.

I wanted to make a chatbot that is better than the AIML types that are so common. Something that would pay attention to who it was talking to and try to learn from that person. It would not guess at an answer when it has no understanding of what was said.

Note: There's more info in the wiki.

## About this program
* It will try to make sense of every word in a sentence. It will never pretend to know its meaning. It will attempt to explain what it's having trouble with. The user may be able to explain new words that are new to it.
* Its database relies on a classification of basic knowledge
* It uses templates to interpret sentences
* Only certain types of words are allowed to fit in the templates
* ID numbers are used identify specific members of a category, usually people could also be pets, buildings database entries start with a number sign followed by the id number* Will expect to know who it's talking to
* Will remember elements of conversations
* Will try to use people to expand it's knowledge
* The source code is documented so that even non-programmers should be able to figure out what's goin on.

## How it works

Sentences are divided into 4 categories: statements, questions, commands and other.
* Statements are used to provide data about a specified noun. The bot will store that data in it's database for future use. The bot will ask about anything that is unfamiliar to it and will point out contradictory info when nessessary
* Questions request data about a specified noun. The bot will respond by providing that data if it's in it's database. It bot will ask about words that are unfamiliar to it.
* The bot will consider commands it receives and may comply if it wants to. This software will eventually be installed in a 4 foot tall mobile robot so if for example it is told to go full speed into a wall it would not do so and tell the user what it thinks of his command.
* Other sentences are dealt with individually.

The program relies mostly on 2 text files to interpret sentences. It's nessessary to understand these files to understand how this progem works
1. The database. This is a list of bits of information about nouns. The essential information about these nouns is what category they are in. For example, "Bob" is classified as a person. A person is a creature. A creature is an object. "Object" is in the root category and is not classified any further. This clasification is used to determine if a sentence makes sense or not.
2. The sentence templates. It's list of sentences with the nouns removed. After each sentence in the list there is the name of a function that will process the sentence further. The function that is chosen is determined by the type of sentence and on the verb used.


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

## Short term goals
* Will ask questions when nothing is typed by the user

## Long term goals
* Will form opinions of the people it talks to
* Will be able to cope with pronouns
* Will be thinking of various things when it's not in a conversation. This activity may have an effect on its mood, may cause it to arrive at some conclusions. It may be prompted to ask related questions. It can be asked "what are you thinking about".

