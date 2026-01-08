push:
	git add .
	git commit -m "chastelib update"
	git push
doxy:
	doxygen Doxyfile
