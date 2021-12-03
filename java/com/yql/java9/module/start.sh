#!/usr/bin/env sh

mkdir -p mods/org.astro mods/com.greetings
javac -d mods/org.astro org/astro/module-info.java org/astro/World.java
javac --module-path mods -d mods/com.greetings com.greetings/module-info.java com.greetings/Main.java
java --module-path mods -m com.greetings/com.greetings.Main
# outputs: Greetings world!
