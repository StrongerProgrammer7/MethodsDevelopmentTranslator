
<sub>** This work is being done as part of the Course Method development translator **</sub> 
# MethodsDevelopmentTranslator
<div>
<p>The repository has translator from C to C#, on the language C++</p>
<h3>Syntax Analisator</h3>
<p>Base file:  (russian language: Vishnikov Y.M. BalabaevaI.Y. PDF):</p>
[](https://github.com/StrongerProgrammer7/MethodsDevelopmentTranslator/files/10741055/_.pdf)
<p>
<h4> 7 Classes </h4>
<ul>
<li>Translator (parent) </li>
<li>LexicalAnalisator (inherit up, parent) </li>
<li>LexicalAnalisator (inherit up, parent) </li>
<li>ReversePolishNotation (inherit up, parent) </li>
<li>SyntaxAnalisator (inherit up, parent) </li>
<li>Translate_csharp (inherit up, parent) </li>
<li>TranslatroFromCToCSharp(inherit up, parent) </li>
</ul>
Users should use last class. Last class using next methods:
<ul>
<li>lexicalAnalyze</li>
<li>reversePolishNotAnalyze</li>
<li>syntaxAnalyze</li>
<li>translateToCSharp</li>
</ul>
</p>
<p> Using:
<pre>TranslatorFromCToCSharp translator
    &emsp;translator.lexicalAnalyze(fileText_C);
    &emsp;translator.reversePolishNotAnalyze();
    &emsp;In condition(if) translator.syntaxAnalyze() == true
    &emsp;translator.translateToCSharp();
</pre>
<p> All method save file to folder "translator_file"</p>
</p>
<h3> TODO </h3>
<p>
Multiple inheritance is present.<br> The reason for this table decision.<br>
Solution <br>
1) What is, and inherit tables (identifiers, constants, etc.)<br>
2) All classes will be inherited from the same class, as they should be "Translator", 
<br>but then you have to pass in the table constructor, and make them open or apply getters.
3)Maybe using pattern "Template"
</p>

<p align="center"><img src="https://user-images.githubusercontent.com/71569051/232427242-16bbfa23-dd7b-4844-9fc9-bade42491847.png"></p>
</div>
<h3>Development tools and Programming Language</h3>
<p align="justify"> Microsoft Visual Studio Profession 2019</p>
<p align="justify"> Language C++, C++/CLI (Windows forms) </p>
</div>
