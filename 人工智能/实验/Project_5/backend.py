import collections
import os
import time
import os

import matplotlib.pyplot as plt
import numpy as np

import nn

use_graphics = True

def maybe_sleep_and_close(seconds):
    if use_graphics and plt.get_fignums():
        time.sleep(seconds)
        for fignum in plt.get_fignums():
            fig = plt.figure(fignum)
            plt.close(fig)
            try:
                # This raises a TclError on some Windows machines
                fig.canvas.start_event_loop(1e-3)
            except:
                pass

def get_data_path(filename):
    path = os.path.join(
        os.path.dirname(__file__), os.pardir, "data", filename)
    if not os.path.exists(path):
        path = os.path.join(
            os.path.dirname(__file__), "data", filename)
    if not os.path.exists(path):
        path = os.path.join(
            os.path.dirname(__file__), filename)
    if not os.path.exists(path):
        raise Exception("Could not find data file: {}".format(filename))
    return path

class Dataset(object):
    def __init__(self, x, y):
        assert isinstance(x, np.ndarray)
        assert isinstance(y, np.ndarray)
        assert np.issubdtype(x.dtype, np.floating)
        assert np.issubdtype(y.dtype, np.floating)
        assert x.ndim == 2
        assert y.ndim == 2
        assert x.shape[0] == y.shape[0]
        self.x = x
        self.y = y

    def iterate_once(self, batch_size):
        assert isinstance(batch_size, int) and batch_size > 0, (
            "Batch size should be a positive integer, got {!r}".format(
                batch_size))
        assert self.x.shape[0] % batch_size == 0, (
            "Dataset size {:d} is not divisible by batch size {:d}".format(
                self.x.shape[0], batch_size))
        index = 0
        while index < self.x.shape[0]:
            x = self.x[index:index + batch_size]
            y = self.y[index:index + batch_size]
            yield nn.Constant(x), nn.Constant(y)
            index += batch_size

    def iterate_forever(self, batch_size):
        while True:
            yield from self.iterate_once(batch_size)

    def get_validation_accuracy(self):
        raise NotImplementedError(
            "No validation data is available for this dataset. "
            "In this assignment, only the Digit Classification and Language "
            "Identification datasets have validation data.")

class PerceptronDataset(Dataset):
    def __init__(self, model):
        points = 500
        x = np.hstack([np.random.randn(points, 2), np.ones((points, 1))])
        y = np.where(x[:, 0] + 2 * x[:, 1] - 1 >= 0, 1.0, -1.0)
        super().__init__(x, np.expand_dims(y, axis=1))

        self.model = model
        self.epoch = 0

        if use_graphics:
            fig, ax = plt.subplots(1, 1)
            limits = np.array([-3.0, 3.0])
            ax.set_xlim(limits)
            ax.set_ylim(limits)
            positive = ax.scatter(*x[y == 1, :-1].T, color="red", marker="+")
            negative = ax.scatter(*x[y == -1, :-1].T, color="blue", marker="_")
            line, = ax.plot([], [], color="black")
            text = ax.text(0.03, 0.97, "", transform=ax.transAxes, va="top")
            ax.legend([positive, negative], [1, -1])
            plt.show(block=False)

            self.fig = fig
            self.limits = limits
            self.line = line
            self.text = text
            self.last_update = time.time()

    def iterate_once(self, batch_size):
        self.epoch += 1

        for i, (x, y) in enumerate(super().iterate_once(batch_size)):
            yield x, y

            if use_graphics and time.time() - self.last_update > 0.01:
                w = self.model.get_weights().data.flatten()
                limits = self.limits
                if w[1] != 0:
                    self.line.set_data(limits, (-w[0] * limits - w[2]) / w[1])
                elif w[0] != 0:
                    self.line.set_data(np.full(2, -w[2] / w[0]), limits)
                else:
                    self.line.set_data([], [])
                self.text.set_text(
                    "epoch: {:,}\npoint: {:,}/{:,}\nweights: {}".format(
                        self.epoch, i * batch_size + 1, len(self.x), w))
                self.fig.canvas.draw_idle()
                self.fig.canvas.start_event_loop(1e-3)
                self.last_update = time.time()

class RegressionDataset(Dataset):
    def __init__(self, model):
        x = np.expand_dims(np.linspace(-2 * np.pi, 2 * np.pi, num=200), axis=1)
        np.random.RandomState(0).shuffle(x)
        self.argsort_x = np.argsort(x.flatten())
        y = np.sin(x)
        super().__init__(x, y)

        self.model = model
        self.processed = 0

        if use_graphics:
            fig, ax = plt.subplots(1, 1)
            ax.set_xlim(-2 * np.pi, 2 * np.pi)
            ax.set_ylim(-1.4, 1.4)
            real, = ax.plot(x[self.argsort_x], y[self.argsort_x], color="blue")
            learned, = ax.plot([], [], color="red")
            text = ax.text(0.03, 0.97, "", transform=ax.transAxes, va="top")
            ax.legend([real, learned], ["real", "learned"])
            plt.show(block=False)

            self.fig = fig
            self.learned = learned
            self.text = text
            self.last_update = time.time()

    def iterate_once(self, batch_size):
        for x, y in super().iterate_once(batch_size):
            yield x, y
            self.processed += batch_size

            if use_graphics and time.time() - self.last_update > 0.1:
                predicted = self.model.run(nn.Constant(self.x)).data
                loss = self.model.get_loss(
                    nn.Constant(self.x), nn.Constant(self.y)).data
                self.learned.set_data(self.x[self.argsort_x], predicted[self.argsort_x])
                self.text.set_text("processed: {:,}\nloss: {:.6f}".format(
                   self.processed, loss))
                self.fig.canvas.draw_idle()
                self.fig.canvas.start_event_loop(1e-3)
                self.last_update = time.time()

class DigitClassificationDataset(Dataset):
    def __init__(self, model):
        mnist_path = get_data_path("mnist.npz")

        with np.load(mnist_path) as data:
            train_images = data["train_images"]
            train_labels = data["train_labels"]
            test_images = data["test_images"]
            test_labels = data["test_labels"]
            assert len(train_images) == len(train_labels) == 60000
            assert len(test_images) == len(test_labels) == 10000
            self.dev_images = test_images[0::2]
            self.dev_labels = test_labels[0::2]
            self.test_images = test_images[1::2]
            self.test_labels = test_labels[1::2]

        train_labels_one_hot = np.zeros((len(train_images), 10))
        train_labels_one_hot[range(len(train_images)), train_labels] = 1

        super().__init__(train_images, train_labels_one_hot)

        self.model = model
        self.epoch = 0

        if use_graphics:
            width = 20  # Width of each row expressed as a multiple of image width
            samples = 100  # Number of images to display per label
            fig = plt.figure()
            ax = {}
            images = collections.defaultdict(list)
            texts = collections.defaultdict(list)
            for i in reversed(range(10)):
                ax[i] = plt.subplot2grid((30, 1), (3 * i, 0), 2, 1,
                                         sharex=ax.get(9))
                plt.setp(ax[i].get_xticklabels(), visible=i == 9)
                ax[i].set_yticks([])
                ax[i].text(-0.03, 0.5, i, transform=ax[i].transAxes,
                           va="center")
                ax[i].set_xlim(0, 28 * width)
                ax[i].set_ylim(0, 28)
                for j in range(samples):
                    images[i].append(ax[i].imshow(
                        np.zeros((28, 28)), vmin=0, vmax=1, cmap="Greens",
                        alpha=0.3))
                    texts[i].append(ax[i].text(
                        0, 0, "", ha="center", va="top", fontsize="smaller"))
            ax[9].set_xticks(np.linspace(0, 28 * width, 11))
            ax[9].set_xticklabels(
                ["{:.1f}".format(num) for num in np.linspace(0, 1, 11)])
            ax[9].tick_params(axis="x", pad=16)
            ax[9].set_xlabel("Probability of Correct Label")
            status = ax[0].text(
                0.5, 1.5, "", transform=ax[0].transAxes, ha="center",
                va="bottom")
            plt.show(block=False)

            self.width = width
            self.samples = samples
            self.fig = fig
            self.images = images
            self.texts = texts
            self.status = status
            self.last_update = time.time()

    def iterate_once(self, batch_size):
        self.epoch += 1

        for i, (x, y) in enumerate(super().iterate_once(batch_size)):
            yield x, y

            if use_graphics and time.time() - self.last_update > 1:
                dev_logits = self.model.run(nn.Constant(self.dev_images)).data
                dev_predicted = np.argmax(dev_logits, axis=1)
                dev_probs = np.exp(nn.SoftmaxLoss.log_softmax(dev_logits))
                dev_accuracy = np.mean(dev_predicted == self.dev_labels)

                self.status.set_text(
                    "epoch: {:d}, batch: {:d}/{:d}, validation accuracy: "
                    "{:.2%}".format(
                        self.epoch, i, len(self.x) // batch_size, dev_accuracy))
                for i in range(10):
                    predicted = dev_predicted[self.dev_labels == i]
                    probs = dev_probs[self.dev_labels == i][:, i]
                    linspace = np.linspace(
                        0, len(probs) - 1, self.samples).astype(int)
                    indices = probs.argsort()[linspace]
                    for j, (prob, image) in enumerate(zip(
                            probs[indices],
                            self.dev_images[self.dev_labels == i][indices])):
                        self.images[i][j].set_data(image.reshape((28, 28)))
                        left = prob * (self.width - 1) * 28
                        if predicted[indices[j]] == i:
                            self.images[i][j].set_cmap("Greens")
                            self.texts[i][j].set_text("")
                        else:
                            self.images[i][j].set_cmap("Reds")
                            self.texts[i][j].set_text(predicted[indices[j]])
                            self.texts[i][j].set_x(left + 14)
                        self.images[i][j].set_extent([left, left + 28, 0, 28])
                self.fig.canvas.draw_idle()
                self.fig.canvas.start_event_loop(1e-3)
                self.last_update = time.time()

    def get_validation_accuracy(self):
        dev_logits = self.model.run(nn.Constant(self.dev_images)).data
        dev_predicted = np.argmax(dev_logits, axis=1)
        dev_accuracy = np.mean(dev_predicted == self.dev_labels)
        return dev_accuracy

class LanguageIDDataset(Dataset):
    def __init__(self, model):
        self.model = model

        data_path = get_data_path("lang_id.npz")

        with np.load(data_path) as data:
            self.chars = data['chars']
            self.language_codes = data['language_codes']
            self.language_names = data['language_names']

            self.train_x = data['train_x']
            self.train_y = data['train_y']
            self.train_buckets = data['train_buckets']
            self.dev_x = data['dev_x']
            self.dev_y = data['dev_y']
            self.dev_buckets = data['dev_buckets']
            self.test_x = data['test_x']
            self.test_y = data['test_y']
            self.test_buckets = data['test_buckets']

        self.epoch = 0
        self.bucket_weights = self.train_buckets[:,1] - self.train_buckets[:,0]
        self.bucket_weights = self.bucket_weights / float(self.bucket_weights.sum())

        self.chars_print = self.chars
        try:
            print(u"Alphabet: {}".format(u"".join(self.chars)))
        except UnicodeEncodeError:
            self.chars_print = "abcdefghijklmnopqrstuvwxyzaaeeeeiinoouuacelnszz"
            print("Alphabet: " + self.chars_print)
            self.chars_print = list(self.chars_print)
            print("""
NOTE: Your terminal does not appear to support printing Unicode characters.
For the purposes of printing to the terminal, some of the letters in the
alphabet above have been substituted with ASCII symbols.""".strip())
        print("")

        # Select some examples to spotlight in the monitoring phase (3 per language)
        spotlight_idxs = []
        for i in range(len(self.language_names)):
            idxs_lang_i = np.nonzero(self.dev_y == i)[0]
            idxs_lang_i = np.random.choice(idxs_lang_i, size=3, replace=False)
            spotlight_idxs.extend(list(idxs_lang_i))
        self.spotlight_idxs = np.array(spotlight_idxs, dtype=int)

        # Templates for printing updates as training progresses
        max_word_len = self.dev_x.shape[1]
        max_lang_len = max([len(x) for x in self.language_names])

        self.predicted_template = u"Pred: {:<NUM}".replace('NUM',
            str(max_lang_len))

        self.word_template = u"  "
        self.word_template += u"{:<NUM} ".replace('NUM', str(max_word_len))
        self.word_template += u"{:<NUM} ({:6.1%})".replace('NUM', str(max_lang_len))
        self.word_template += u" {:<NUM} ".replace('NUM',
            str(max_lang_len + len('Pred: ')))
        for i in range(len(self.language_names)):
            self.word_template += u"|{}".format(self.language_codes[i])
            self.word_template += "{probs[" + str(i) + "]:4.0%}"

        self.last_update = time.time()

    def _encode(self, inp_x, inp_y):
        xs = []
        for i in range(inp_x.shape[1]):
            if np.all(inp_x[:,i] == -1):
                break
            assert not np.any(inp_x[:,i] == -1), (
                "Please report this error in the project: batching by length was done incorrectly in the provided code")
            x = np.eye(len(self.chars))[inp_x[:,i]]
            xs.append(nn.Constant(x))
        y = np.eye(len(self.language_names))[inp_y]
        y = nn.Constant(y)
        return xs, y

    def _softmax(self, x):
        exp = np.exp(x - np.max(x, axis=-1, keepdims=True))
        return exp / np.sum(exp, axis=-1, keepdims=True)

    def _predict(self, split='dev'):
        if split == 'dev':
            data_x = self.dev_x
            data_y = self.dev_y
            buckets = self.dev_buckets
        else:
            data_x = self.test_x
            data_y = self.test_y
            buckets = self.test_buckets

        all_predicted = []
        all_correct = []
        for bucket_id in range(buckets.shape[0]):
            start, end = buckets[bucket_id]
            xs, y = self._encode(data_x[start:end], data_y[start:end])
            predicted = self.model.run(xs)

            all_predicted.extend(list(predicted.data))
            all_correct.extend(list(data_y[start:end]))

        all_predicted_probs = self._softmax(np.asarray(all_predicted))
        all_predicted = np.asarray(all_predicted).argmax(axis=-1)
        all_correct = np.asarray(all_correct)

        return all_predicted_probs, all_predicted, all_correct

    def iterate_once(self, batch_size):
        assert isinstance(batch_size, int) and batch_size > 0, (
            "Batch size should be a positive integer, got {!r}".format(
                batch_size))
        assert self.train_x.shape[0] >= batch_size, (
            "Dataset size {:d} is smaller than the batch size {:d}".format(
                self.train_x.shape[0], batch_size))

        self.epoch += 1

        for iteration in range(self.train_x.shape[0] // batch_size):
            bucket_id = np.random.choice(self.bucket_weights.shape[0], p=self.bucket_weights)
            example_ids = self.train_buckets[bucket_id, 0] + np.random.choice(
                self.train_buckets[bucket_id, 1] - self.train_buckets[bucket_id, 0],
                size=batch_size)

            yield self._encode(self.train_x[example_ids], self.train_y[example_ids])

            if use_graphics and time.time() - self.last_update > 0.5:
                dev_predicted_probs, dev_predicted, dev_correct = self._predict()
                dev_accuracy = np.mean(dev_predicted == dev_correct)

                print("epoch {:,} iteration {:,} validation-accuracy {:.1%}".format(
                    self.epoch, iteration, dev_accuracy))

                for idx in self.spotlight_idxs:
                    correct = (dev_predicted[idx] == dev_correct[idx])
                    word = u"".join([self.chars_print[ch] for ch in self.dev_x[idx] if ch != -1])

                    print(self.word_template.format(
                        word,
                        self.language_names[dev_correct[idx]],
                        dev_predicted_probs[idx, dev_correct[idx]],
                        "" if correct else self.predicted_template.format(
                            self.language_names[dev_predicted[idx]]),
                        probs=dev_predicted_probs[idx,:],
                    ))

                self.last_update = time.time()

    def get_validation_accuracy(self):
        dev_predicted_probs, dev_predicted, dev_correct = self._predict()
        dev_accuracy = np.mean(dev_predicted == dev_correct)
        return dev_accuracy


def main():
    import models
    model = models.PerceptronModel(3)
    dataset = PerceptronDataset(model)
    model.train(dataset)

    model = models.RegressionModel()
    dataset = RegressionDataset(model)
    model.train(dataset)

    model = models.DigitClassificationModel()
    dataset = DigitClassificationDataset(model)
    model.train(dataset)

    model = models.LanguageIDModel()
    dataset = LanguageIDDataset(model)
    model.train(dataset)

if __name__ == "__main__":
    main()
