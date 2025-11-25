FROM debian:stable-slim
RUN apt-get update && apt install -y iproute2 iputils-ping nmap
CMD ["sleep", "infinity"]
