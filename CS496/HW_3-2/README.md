*Assignment 3*

**Overview**

This week you will implement a web based API to manipulate the data in your non-relational database you planned in part 1.

There should be at least one appropriate use of each of the 4 major HTTP verbs, GET, POST, PUT and DELETE.

It should be possible to do all the actions that make sense for your schema, both from a user side and an admin side. You do not need to implement any authentication or authorization, however you may do so if you feel so inclined.

It should be possible to add things and to associate things. In the IRC Channel example, I was able to create IRC Channels, create Mods and add Mods to Channels. I expect similar from your projects. Additionally you will need to be able to delete entities as well. When you do this, don't forget to clean up any references to that entity in other entities. Because you are not using a relational database it is your responsibility to clean up after yourself.

**Requirements**

Program Requirements:
    1. You should have a live functioning API that is publicly accessible or that you provide the needed credentials to access.
    2. You should provide a full set of tests. These could be curl calls, a python script, commands entered into a browser plugin etc. It should show that you are able to do all the above actions. Additionally make sure they show that when an element is deleted, references to that element are cleaned up as well.
    3. You should provide the results of those tests including explanations for any tests that failed. (Things should ideally not fail, but if they do, it is better to explain it than to ignore it)
    4. This should be hosted on some variety of cloud platform and use a non-relational database to store the data.

Documentation Requirements:
    1. An explanation of the URL structure used to access resources
    2. A description of which RESTful constraints you met and which you did not (you do not need to make a RESTful app, but you do need to know why it does not meet all the constraints of a RESTful API)
    3. A discussion of any changes you needed to make to the schema from last week
    4. Having finished the API, what you would have done differently

***You should include a .zip file with all of your source code. This file should also include the previously mentioned pdf.*** 

