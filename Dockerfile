FROM debian:stable-slim
RUN apt-get update && apt-get install -y iproute2 iputils-ping
RUN echo >command './ft_malcolm 172.18.0.2 x 172.18.0.3 x'
CMD ["sleep", "infinity"]