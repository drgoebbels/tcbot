FROM alpine

WORKDIR /apps
COPY . /apps

RUN apk add --update make gcc libc-dev
RUN make

CMD ["./tcbot"]

