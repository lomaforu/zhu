path="/home/zyd/workfile/clion/build"
build="/build"
name="/zyd/"

numb=$(echo $path | tr -cd '/' | wc -c)

if [ $numb > 3 ]; then
	if [[ $path == *$build ]] && [[ $path == *$name* ]]; then
		if [ -d "$path" ]; then
			cd $path
			ls | grep -v "build.sh" | xargs rm -rf
			cmake ..
			make -j 16
		else
			echo 'not exits folder:'$path''
		fi
	else
		echo 'find no build folder:'$path''
	fi
else
	echo 'folder layer less 4'
fi

