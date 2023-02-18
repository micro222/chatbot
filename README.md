A text-based learning robot that tries to get to know its users. It runs on a Raspberry Pi and Windows. I've been working on this chatbot on and off for about 20 years, and while I've made a lot of progress, there's a great deal of work left to do.

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

The program first separates the nouns from the rest of the sentence. I refer to the rest of the sentence as a template. From the template the program can determine wether the sentence is a question, statement, command or something else. The templates that the program recognizes are in a file called templates2.txt. Each template has it's own function to process it and is specified in that file. The functions are in handle.c.

So let's run through an example. The user types "grass is green". The nouns are removed and the template is "* is *". The purpose of this sentence is to inform the program that the specified attribute (the color green) is to be applied to the specified object or substance (grass). The function "handle_attribute_statement" is called with grass and green as arguments.

This function will concider 7 posibilities
* 1   grass is not in the database
* 2   grass is neither an object or a substance and therefore can't have a color
* 3   green is not in the database
* 4   green is in the database but is not an attribute
* 5   the info is already in the database
* 6   the info contradicts what is in the database
* 7   the sentence is without issues

If 7 applies, the programm will type "I'll take a note of that" and the following entry will be added to the database (general.txt)
...
              grass > color: green;
...              
If 1 to 6, the program will inform the user of the issue.

Questions are answered by looking them up in the database. 

The program will consider commands it receives and may comply if it wants to. This software will eventually be installed in a 4 foot tall mobile robot so if for example it is told to go full speed into a wall it would not do so and tell the user what it thinks of his command. 

Other sentences are dealt with individually.



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

