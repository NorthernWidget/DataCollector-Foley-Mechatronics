%% $Header$
%% Reykjavik University Report Class file
%% Initial version by Joe Foley <foley@RU.IS>
%% Created on 2013-02-04
%% This code is distributed under the Perl Artistic License
%% http://language.per.com/misc/Artistic.html
%% Some code is derived from the IEEE LaTeX class, RU ad-hoc
%% wireless project labeling system, and RU CS M.Sc. Thesis and Report template

%% --------------- Identification ----------------------------
\newcommand{\fileversion@rureport}{v0.1}
\newcommand{\filedate@rureport}{2013/02/04}
\newcommand{\fileauthor@rureport}{Joe Foley, foley@RU.IS}
\ProvidesClass{rureport}[\filedate@rureport by \fileauthor@rureport]
\NeedsTeXFormat{LaTeX2e}
%\typeout{Reykjavik University Report Basic template for School of
 % Science and Engineering: \fileversion@rureport from <\filedate@rureport>, by \fileauthor@rureport}

%% ---------------- Initial Code -----------------------------
\RequirePackage{ifthen}
% This package allows you to create conditionals on booleans
\RequirePackage{ifdraft}
\newboolean{svn}

%% ---------------- Declaration of Options--------------------
%% Remember that we have \AtEndOfClass{},\AtEndOfPackage{}
%%     \AtBeginDocument{}, \AtEndDocument{}
%% If you want execution conditional on file existence
%%     \IfFileExists{filename}{true}{false}
%%     \InputIfFileExists{filename}{true}{false}
%% For error reporting
%%     \ClassError{class-name}{error-text}{help-text}
%%     \PackageError{class-name}{error-text}{help-text}
%\DeclareOption{rulogotitle}{
% % TODO: finish this.  RU logo on the title page
% 
% }
%% otherwise, just a generic title page

\DeclareOption{svn}{
  \setboolean{svn}{true}
}

\DeclareOption{isbabel}{ % set Icelandic labels on figures, tables, etc.
  \AtEndOfClass{
    \RequirePackage[icelandic]{babel}
  }
}



%% now we pass the remaining unused options to our parent class
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{article}}
%% ---------------- Execution of Options -----------------------------
\ProcessOptions \relax % this stops searching for a * in
                       % \ProcessOtions*

%% Alternative way to subclass.  Disable the other option processing
%% if you enable it.  This will dump all options onto the parent class
%\ProcessOptions\LoadClassWithOptions{article}
%% ---------------- Package Loading -----------------------------
\LoadClass{article}  % our parent class.  Article is a little easier
                     % to work with than the report class.
\RequirePackage[T1]{fontenc}
\RequirePackage[utf8]{inputenc}  % allows UTF encoding, needed for Icelandic characters
\RequirePackage[margin=2cm,a4paper]{geometry}
%% Some slighly more sensible margins on an A4 page
%% This can be tuned for your given report

% Some useful fonts, particularly for listings
\RequirePackage{lipsum}
\RequirePackage{courier}




\ifthenelse{\boolean{svn}}{
	% switching to the svn-multi package which is much smarter
  %\RequirePackage[today,fancyhdr]{svninfo} 
  % grab the SVN revision information from a \svninfo $Id: rureport.cls 350 2014-10-08 12:40:38Z foley@ru.is $
  %% today option sets the current day to the latest SVN date
  %% Remember that you will need to put a \svninfo and \svnKeyword
  %% into your document or it will only grab the revision information
  %% of the class file!  Also, you will need to set the svn:keywords properties.
  %\svnInfo $Id: rureport.cls 350 2014-10-08 12:40:38Z foley@ru.is $
  %\svnKeyword $HeadURL: https://svn.ru.is/projects/cabin-environment/project/cabin%20air%20quality/data-collection/doc/rureport.cls $
  \RequirePackage{svn-multi}
}{ % If svninfo not installed, we load it invisibly to avoid problems
  %\RequirePackage[notoday,nofancy,final]{svninfo} 
    \RequirePackage{svn-multi}
}

\RequirePackage{fancyhdr}
%% Nice options for tweaking the header and footer

\RequirePackage[final]{graphicx}
%% We give the "final" option so that it always includes graphics
%% Take out this option if you want draft mode to skip pics

\DeclareGraphicsExtensions{.pdf,.jpeg,.jpg,.png,.gif,.PDF,.JPEG,.JPG,.PNG,.GIF}
%% The extensions that it will search for as valid graphics files
%% We need To include the UPPERCASE versions For windows people

\graphicspath{{graphics/}{Graphics/}{./}}
%% This is a list of folders to search for graphics files to include
%% Each path should be in a {}.  
%% Make sure that the upper/lowercase of the letters matches the folder or
%% you may have weird problems with partners using other operating systems.
%% Note that you don't have to put the folder where the .tex file is, it is
%% included automatically, though it is bad practice to put your 
%% graphics there

\RequirePackage[final]{pdfpages}
%% The "pdfpages" package lets you include PDF documents into your
%% document but keeps the formatting consistent (headers, footers,
%% etc.)

%\RequirePackage{lastpage}
% The "lastpage" package allows you to set a command that knows
% what the last page was e.g. page 1 of 4

%% declare the paths(s) where you graphics files can be found
%% This allows you to skip putting the full path in
%% If you put a // at the end, it will recursively search for graphics
%% files, but be careful!
\RequirePackage{pseudocode}


\RequirePackage{url}
%% The url package typesets url's and unix file paths nicely when they
%% become long.  Warning: windows paths such as C:\window do not work!
%% You need another verbatime to make those typeset properly.

\RequirePackage{xspace}
%% The xspace package will try to figure out if you meant to have a
%% space after a new command if you don't give it any arguments (in
%% braces: {} ).  

%% Creates macros to adjust the line spacing more easily
%\onehalfspacing
%% By default, set to 1.5 spacing
\linespread{1.3}  % this method does not require the setspace package

% % some font package possibilities
% % From http://www.macfreek.nl/memory/Fonts_in_LaTeX
%\RequirePackage{lmodern}
%\RequirePackage{times}
%\RequirePackage{palatino}
%\RequirePackage{bookman}
%\RequirePackage{newcent}
\RequirePackage{helvet}

% The old template uses san-serif, let's also do so 
\renewcommand{\familydefault}{\sfdefault}

%% ---------------- Main Code -----------------------------
%%  Remember that we can declar commands (to make fragile things safe)
%%  The * form is for ``short'' commands, not longer than a paragraph
%%       \DeclareRobustCommand{cmd}[num][default]{definition}
%%       \DeclareRobustCommand*{cmd}[num][default]{definition}
%%  For checking if commands are redefined
%%       \CheckCommand{cmd}[num][default]{definition}

% this is for the picture environment
\setlength{\unitlength}{1cm}

\RequirePackage{amsfonts}
\RequirePackage{siunitx}  % replacement for SIunits, less problems
%% AMS is American Mathematics Society.  They have a bunch of nice
%% math fonts and symbols

\RequirePackage{examplep} % another verbatim environment
\RequirePackage[final]{listings} % force final or included files are skipped, invisibly!
% This allows you to include code easily
% \begin{lstlisting}[language=bash]
%  $ wget http://blah
% \end{lstlisting}
% or for simpler snippets
%  \lstinline^cp -rp foo bar^
%  You can replace ^ with any character not in your code
\lstset{%
	language=, %default similar to verbatim
  basicstyle=\footnotesize\ttfamily,%
  frame=lines,%
  breaklines=true,%
  postbreak=\raisebox{0ex}[0ex][0ex]{\ensuremath{\color{red}\hookrightarrow\space}}, % red arrow
  % from http://tex.stackexchange.com/questions/116534/lstlisting-line-wrapping
}
% Here are listings macros I use a lot
\newcommand{\fpath}{\lstinline}  % magic, do not try to give it arguments
\newcommand{\shcmd}{\lstinline}  
% ex:  \fpath{\\AFS\.rnd.ru.is\course\T-411-MECH}



\RequirePackage{subfig}
%% Nice package for making sub figures inside of a figure.  Keeps all
%% the reference labels correct and makes "sub captions"
% % WARNING: this is completely different than the subfigure package


\RequirePackage[layout=inline]{fixme}
% FIXME system for making notes to each other for what needs to 
% be completed in a group document.

% internal layouts: inline, margin, footnote, index, marginclue
% % Warning! The pdf external layouts do not play well with hyperref
% % and must be loaded by doing \fxuselayouts{}
% external layouts: marginnote, pdfnote, pdfmargin, pdfsignote, pdfsigmargin
%     pdfcnote, pdfcmargin, pdfcsignote, pdfcsigmargin
%  pdfc stands for pdf color
%\fxuselayouts{pdfcmargin}


%%%% Some packages that RUMSC.sty includes.  Enable as needed
%\RequirePackage[absolute]{textpos}

%\RequirePackage[overload]{textcase}

%\RequirePackage{color}
%\definecolor{rugray}{rgb}{0.2,0.2,0.2}
%\definecolor{rured}{rgb}{0.84,0.10,0.13}
%% The "color" package allows us to set the color of text and other
%% objects in a document

\AtBeginDocument{
  \RequirePackage[final]{hyperref}
%% Hyper references (clickable links) in the document.  Very nice, but
%% MUST be the last package loaded.  If you are in draft mode, it will
%% disable itself, so we force it to be in final mode.
}

%% Commonly used notation/abbrevs, converted into latex commands:
\renewcommand{\d}[1]{\;\textsf{d}#1}
\newcommand{\pd}[1]{\partial #1}
\newcommand{\D}{\;\textsf{D}}
\providecommand{\e}[1]{\ensuremath{\times 10^{#1}}}
%% Extremely common abbreviations
\newcommand{\kg}{\si{\kilo\gram}}
\newcommand{\mA}{\si{\milli\ampere}}
\newcommand{\amp}{\si{\ampere}}

%% Common way to make a centered picture that
%% has a caption, label, and is centered 
\newcommand{\cfigure}[2]{\begin{figure}[h]
\centering %
\includegraphics{#1}%
\caption{#2\label{fig:#1}}%
\end{figure}%
}
\newcommand{\cfiguresize}[3]{\begin{figure}[h]
\centering %
\includegraphics[#3]{#1}%
\caption{#2\label{fig:#1}}%
\end{figure}%
}

%% Some commonly used fonts in RUMSc.sty
%\def\twttb{\fontencoding{T1}\fontfamily{pmt}\fontseries{b}\fontshape{n}\fontsize{24pt}{28pt}\selectfont}
%\def\fftntb{\fontencoding{T1}\fontfamily{ptm}\fontseries{m}\fontshape{n}\fontsize{15pt}{20pt}\selectfont}
%\def\twvtr{\fontencoding{T1}\fontfamily{ptm}\fontseries{m}\fontshape{n}\fontsize{14pt}{16pt}\selectfont}
%\def\tentm{\fontencoding{T1}\fontfamily{ptm}\fontseries{m}\fontshape{n}\fontsize{10pt}{12pt}\selectfont}
%\def\eigtm{\fontencoding{T1}\fontfamily{ptm}\fontseries{m}\fontshape{n}\fontsize{8pt}{10pt}\selectfont}     
%\def\tenhv{\fontencoding{T1}\fontfamily{phv}\fontseries{m}\fontshape{n}\fontsize{10pt}{12pt}\selectfont}

%% ----- Setup page layout, including title page ----- %%

%% First we need to create some "variables" with defaults and commands
%% defaults
\newcommand{\title@rureport}{Iceland 3000}
\newcommand{\shorttitle@rureport}{Ice 3000}
\newcommand{\author@rureport}{Snorri Snorrason}
\newcommand{\course@rureport}{VT-3000 Liberation 1700}
\newcommand{\instructor@rureport}{Bob Jones}

%% commands to set them
\newcommand{\shorttitle}[1]{\renewcommand{\shorttitle@rureport}{\ifdraft{DRAFT:}{} #1}}
\renewcommand{\title}[1]{\renewcommand{\title@rureport}{#1}\shorttitle{#1}}
% assume that the short title should be same as normal title unless specified
\renewcommand{\author}[1]{\renewcommand{\author@rureport}{#1}}
\newcommand{\course}[1]{\renewcommand{\course@rureport}{#1}}
\newcommand{\instructor}[1]{\renewcommand{\instructor@rureport}{#1}}



\renewcommand{\maketitle}{
  {\centering%
    {\LARGE
      \vspace*{4cm}%
      \includegraphics{ru-logo}\\\vspace{\baselineskip}
      \ifdraft{\fbox{DRAFT!  DO NOT SUBMIT!}\\}{}
      {\huge \title@rureport\\}
      \author@rureport\\
      \vspace{\baselineskip}
      \course@rureport\\
      Instructor: \instructor@rureport\\
    }
    {\large
      \vfil
      \today\\
    	\ifthenelse{\boolean{svn}}{SVN Revision \svnrev}{}  
      \vfil
    }
    \ifthenelse{\boolean{svn}}{{\scriptsize \url{\svnmainurl}}}{}
  }
  \newpage
}

\pagestyle{fancyplain} % rest of the document should have fancy headers
                       % but not too fancy
\thispagestyle{empty} % title page should not have the headers and
                      % footers

\lhead{\shorttitle@rureport}
\rhead{\leftmark}
\setlength{\headheight}{15pt} % to make fancyhdr happy

%% on the rest of the pages, these will be the headers.  The first letter
%% indicates which side.  "r" for right, "c" for center, "l" for left 
%\lfooter{}
%\rfooter{}
%% set these for if you need to adjust the footers. 

%% ---------------- End of Class --------------------------

