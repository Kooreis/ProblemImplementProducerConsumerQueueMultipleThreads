enqueue(item) {
        this.queue.push(item);
        this.process();
    }

    async process() {
        if (this.queue.length > 0 && !this.isProcessing) {
            this.isProcessing = true;
            let item = this.queue.shift();
            await this.consume(item);
            this.isProcessing = false;
            this.process();
        }
    }