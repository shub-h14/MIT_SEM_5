if command -v dpkg > /dev/null; then
    echo "Listing installed packages on a Debian/Ubuntu-based system:"
    dpkg --get-selections | grep -v deinstall
elif command -v snap > /dev/null; then
    echo "Listing installed Snap packages:"
    snap list
else
    echo "No recognized package manager found."
    exit 1
fi
