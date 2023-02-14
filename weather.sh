#!/bin/sh

# Globals

URL="https://forecast.weather.gov/zipcity.php"
ZIPCODE=46556
FORECAST=0
CELSIUS=0

# Functions

usage() {
    cat 1>&2 <<EOF
Usage: $(basename $0) [zipcode]

-c    Use Celsius degrees instead of Fahrenheit for temperature
-f    Display forecast text after the temperature

If zipcode is not provided, then it defaults to $ZIPCODE.
EOF
    exit $1
}

weather_information() {
    # Fetch weather information from URL based on ZIPCODE
    curl -sL "$URL?inputstring=$ZIPCODE"
}

temperature() {
    # Extract temperature information from weather source
    weather_information | grep -o '<p class="myforecast-current-lrg">.*&deg;F</p>' | grep -o '[0-9][0-9]*&deg;F' | grep -o '[0-9][0-9]*' 
}


forecast() {
    # Extract forecast information from weather source
    weather_information | grep -o '<p class="myforecast-current">.*</p>' | grep -o '>.*<' | grep -o '[^<>]*' | grep -v '^$' | xargs echo  
}
 
# Parse Command Line Options

while [ $# -gt 0 ]; do
    case $1 in
        -h) usage 0;;
        -f) FORECAST=1;;
        -c) CELSIUS=1;;
        *) ZIPCODE="$1";;
	-*) usage=1;; 
    esac
    shift
done

# Display Information

temp=$(temperature)
if [ $CELSIUS -eq 1 ]; then
temp=$(echo "scale=1; ($temp-32)*5/9" | bc | xargs printf "%.0f")
temp="${temp}"
fi
echo "Temperature: $temp degrees"
if [ $FORECAST -eq 1 ]; then
fc=$(forecast)
echo "Forecast:    $fc"
fi
