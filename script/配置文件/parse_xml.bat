@echo off
cd /d %~dp0

if exist result rd /s /q result
md result


set /p var=������xml:

if exist Python34\python.exe (
	Python34\python.exe parse_xml.py %var%
) else (
	python parse_xml.py %var%
)


pause;