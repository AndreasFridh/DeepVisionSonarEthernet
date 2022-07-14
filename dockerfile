FROM amytabb/docker_ubuntu16_essentials

# Install python3
RUN     apt-get update
RUN     apt-get install -y python3

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









