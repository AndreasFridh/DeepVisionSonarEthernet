# Base image for deploying on multi arch
FROM debian:9

LABEL maintainer="andreas@pyramind.se"

# Install python3
RUN apt-get clean
RUN apt-get update --allow-insecure-repositories
RUN apt-get install -y python g++ make
# Copy Sonar C++ code to image
COPY EthernetSonar /EthernetSonar

# Change working directory
WORKDIR /EthernetSonar

RUN touch *
RUN make -B
RUN chmod -R 777 EthernetSonar
RUN chmod +x run.sh

CMD sh ./run.sh

EXPOSE 80










