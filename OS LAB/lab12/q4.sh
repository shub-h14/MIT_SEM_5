if command -v rpm > /dev/null; then
    echo "Listing all installed RPM packages:"
    rpm -qa
else
    echo "This system does not appear to use RPM ;("
    exit 1
fi
