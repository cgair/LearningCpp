# Why do Makefiles exist?
> Makefiles are used to help decide which parts of a large program need to be recompiled.

# Makefile Syntax
A Makefile consists of a set of rules. A rule generally looks like this:
```bash
targets: prerequisites
	command
	command
	command
```
* The targets are file names, separated by spaces. Typically, there is only one per rule.
* The commands are a series of steps typically used to make the target(s). These need to start with a tab character, not spaces.
* The prerequisites are also file names, separated by spaces. These files need to exist before the commands for the target are run. These are also called dependencies

# Automatic Variables
```bash
$@: the target of the rule.
$<: the first prerequisite of the rule.
$^: the list of all prerequisites of the rule
```

**See gnu make manual P130 10.5.3 Automatic Variables**

# See also
* [Learn Makefiles With the tastiest examples](https://makefiletutorial.com/#top)