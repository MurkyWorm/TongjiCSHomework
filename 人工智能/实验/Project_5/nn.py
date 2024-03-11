import numpy as np

def format_shape(shape):
    return "x".join(map(str, shape)) if shape else "()"

class Node(object):
    def __repr__(self):
        return "<{} shape={} at {}>".format(
            type(self).__name__, format_shape(self.data.shape), hex(id(self)))

class DataNode(Node):
    """
    DataNode is the parent class for Parameter and Constant nodes.

    You should not need to use this class directly.
    """
    def __init__(self, data):
        self.parents = []
        self.data = data

    def _forward(self, *inputs):
        return self.data

    @staticmethod
    def _backward(gradient, *inputs):
        return []

class Parameter(DataNode):
    """
    A Parameter node stores parameters used in a neural network (or perceptron).

    Use the the `update` method to update parameters when training the
    perceptron or neural network.
    """
    def __init__(self, *shape):
        assert len(shape) == 2, (
            "Shape must have 2 dimensions, instead has {}".format(len(shape)))
        assert all(isinstance(dim, int) and dim > 0 for dim in shape), (
            "Shape must consist of positive integers, got {!r}".format(shape))
        limit = np.sqrt(3.0 / np.mean(shape))
        data = np.random.uniform(low=-limit, high=limit, size=shape)
        super().__init__(data)

    def update(self, direction, multiplier):
        assert isinstance(direction, Constant), (
            "Update direction must be a {} node, instead has type {!r}".format(
                Constant.__name__, type(direction).__name__))
        assert direction.data.shape == self.data.shape, (
            "Update direction shape {} does not match parameter shape "
            "{}".format(
                format_shape(direction.data.shape),
                format_shape(self.data.shape)))
        assert isinstance(multiplier, (int, float)), (
            "Multiplier must be a Python scalar, instead has type {!r}".format(
                type(multiplier).__name__))
        self.data += multiplier * direction.data
        assert np.all(np.isfinite(self.data)), (
            "Parameter contains NaN or infinity after update, cannot continue")

class Constant(DataNode):
    """
    A Constant node is used to represent:
    * Input features
    * Output labels
    * Gradients computed by back-propagation

    You should not need to construct any Constant nodes directly; they will
    instead be provided by either the dataset or when you call `nn.gradients`.
    """
    def __init__(self, data):
        assert isinstance(data, np.ndarray), (
            "Data should be a numpy array, instead has type {!r}".format(
                type(data).__name__))
        assert np.issubdtype(data.dtype, np.floating), (
            "Data should be a float array, instead has data type {!r}".format(
                data.dtype))
        super().__init__(data)

class FunctionNode(Node):
    """
    A FunctionNode represents a value that is computed based on other nodes.
    The FunctionNode class performs necessary book-keeping to compute gradients.
    """
    def __init__(self, *parents):
        assert all(isinstance(parent, Node) for parent in parents), (
            "Inputs must be node objects, instead got types {!r}".format(
                tuple(type(parent).__name__ for parent in parents)))
        self.parents = parents
        self.data = self._forward(*(parent.data for parent in parents))

class Add(FunctionNode):
    """
    Adds matrices element-wise.

    Usage: nn.Add(x, y)
    Inputs:
        x: a Node with shape (batch_size x num_features)
        y: a Node with the same shape as x
    Output:
        a Node with shape (batch_size x num_features)
    """
    @staticmethod
    def _forward(*inputs):
        assert len(inputs) == 2, "Expected 2 inputs, got {}".format(len(inputs))
        assert inputs[0].ndim == 2, (
            "First input should have 2 dimensions, instead has {}".format(
                inputs[0].ndim))
        assert inputs[1].ndim == 2, (
            "Second input should have 2 dimensions, instead has {}".format(
                inputs[1].ndim))
        assert inputs[0].shape == inputs[1].shape, (
            "Input shapes should match, instead got {} and {}".format(
                format_shape(inputs[0].shape), format_shape(inputs[1].shape)))
        return inputs[0] + inputs[1]

    @staticmethod
    def _backward(gradient, *inputs):
        assert gradient.shape == inputs[0].shape
        return [gradient, gradient]

class AddBias(FunctionNode):
    """
    Adds a bias vector to each feature vector

    Usage: nn.AddBias(features, bias)
    Inputs:
        features: a Node with shape (batch_size x num_features)
        bias: a Node with shape (1 x num_features)
    Output:
        a Node with shape (batch_size x num_features)
    """
    @staticmethod
    def _forward(*inputs):
        assert len(inputs) == 2, "Expected 2 inputs, got {}".format(len(inputs))
        assert inputs[0].ndim == 2, (
            "First input should have 2 dimensions, instead has {}".format(
                inputs[0].ndim))
        assert inputs[1].ndim == 2, (
            "Second input should have 2 dimensions, instead has {}".format(
                inputs[1].ndim))
        assert inputs[1].shape[0] == 1, (
            "First dimension of second input should be 1, instead got shape "
            "{}".format(format_shape(inputs[1].shape)))
        assert inputs[0].shape[1] == inputs[1].shape[1], (
            "Second dimension of inputs should match, instead got shapes {} "
            "and {}".format(
                format_shape(inputs[0].shape), format_shape(inputs[1].shape)))
        return inputs[0] + inputs[1]

    @staticmethod
    def _backward(gradient, *inputs):
        assert gradient.shape == inputs[0].shape
        return [gradient, np.sum(gradient, axis=0, keepdims=True)]

class DotProduct(FunctionNode):
    """
    Batched dot product

    Usage: nn.DotProduct(features, weights)
    Inputs:
        features: a Node with shape (batch_size x num_features)
        weights: a Node with shape (1 x num_features)
    Output: a Node with shape (batch_size x 1)
    """
    @staticmethod
    def _forward(*inputs):
        assert len(inputs) == 2, "Expected 2 inputs, got {}".format(len(inputs))
        assert inputs[0].ndim == 2, (
            "First input should have 2 dimensions, instead has {}".format(
                inputs[0].ndim))
        assert inputs[1].ndim == 2, (
            "Second input should have 2 dimensions, instead has {}".format(
                inputs[1].ndim))
        assert inputs[1].shape[0] == 1, (
            "First dimension of second input should be 1, instead got shape "
            "{}".format(format_shape(inputs[1].shape)))
        assert inputs[0].shape[1] == inputs[1].shape[1], (
            "Second dimension of inputs should match, instead got shapes {} "
            "and {}".format(
                format_shape(inputs[0].shape), format_shape(inputs[1].shape)))
        return np.dot(inputs[0], inputs[1].T)

    @staticmethod
    def _backward(gradient, *inputs):
        # assert gradient.shape[0] == inputs[0].shape[0]
        # assert gradient.shape[1] == 1
        # return [np.dot(gradient, inputs[1]), np.dot(gradient.T, inputs[0])]
        raise NotImplementedError(
            "Backpropagation through DotProduct nodes is not needed in this "
            "assignment")

class Linear(FunctionNode):
    """
    Applies a linear transformation (matrix multiplication) to the input

    Usage: nn.Linear(features, weights)
    Inputs:
        features: a Node with shape (batch_size x input_features)
        weights: a Node with shape (input_features x output_features)
    Output: a node with shape (batch_size x output_features)
    """
    @staticmethod
    def _forward(*inputs):
        assert len(inputs) == 2, "Expected 2 inputs, got {}".format(len(inputs))
        assert inputs[0].ndim == 2, (
            "First input should have 2 dimensions, instead has {}".format(
                inputs[0].ndim))
        assert inputs[1].ndim == 2, (
            "Second input should have 2 dimensions, instead has {}".format(
                inputs[1].ndim))
        assert inputs[0].shape[1] == inputs[1].shape[0], (
            "Second dimension of first input should match first dimension of "
            "second input, instead got shapes {} and {}".format(
                format_shape(inputs[0].shape), format_shape(inputs[1].shape)))
        return np.dot(inputs[0], inputs[1])

    @staticmethod
    def _backward(gradient, *inputs):
        assert gradient.shape[0] == inputs[0].shape[0]
        assert gradient.shape[1] == inputs[1].shape[1]
        return [np.dot(gradient, inputs[1].T), np.dot(inputs[0].T, gradient)]

class ReLU(FunctionNode):
    """
    An element-wise Rectified Linear Unit nonlinearity: max(x, 0).
    This nonlinearity replaces all negative entries in its input with zeros.

    Usage: nn.ReLU(x)
    Input:
        x: a Node with shape (batch_size x num_features)
    Output: a Node with the same shape as x, but no negative entries
    """
    @staticmethod
    def _forward(*inputs):
        assert len(inputs) == 1, "Expected 1 input, got {}".format(len(inputs))
        assert inputs[0].ndim == 2, (
            "Input should have 2 dimensions, instead has {}".format(
                inputs[0].ndim))
        return np.maximum(inputs[0], 0)

    @staticmethod
    def _backward(gradient, *inputs):
        assert gradient.shape == inputs[0].shape
        return [gradient * np.where(inputs[0] > 0, 1.0, 0.0)]

class SquareLoss(FunctionNode):
    """
    This node first computes 0.5 * (a[i,j] - b[i,j])**2 at all positions (i,j)
    in the inputs, which creates a (batch_size x dim) matrix. It then calculates
    and returns the mean of all elements in this matrix.

    Usage: nn.SquareLoss(a, b)
    Inputs:
        a: a Node with shape (batch_size x dim)
        b: a Node with shape (batch_size x dim)
    Output: a scalar Node (containing a single floating-point number)
    """
    @staticmethod
    def _forward(*inputs):
        assert len(inputs) == 2, "Expected 2 inputs, got {}".format(len(inputs))
        assert inputs[0].ndim == 2, (
            "First input should have 2 dimensions, instead has {}".format(
                inputs[0].ndim))
        assert inputs[1].ndim == 2, (
            "Second input should have 2 dimensions, instead has {}".format(
                inputs[1].ndim))
        assert inputs[0].shape == inputs[1].shape, (
            "Input shapes should match, instead got {} and {}".format(
                format_shape(inputs[0].shape), format_shape(inputs[1].shape)))
        return np.mean(np.square(inputs[0] - inputs[1]) / 2)

    @staticmethod
    def _backward(gradient, *inputs):
        assert np.asarray(gradient).ndim == 0
        return [
            gradient * (inputs[0] - inputs[1]) / inputs[0].size,
            gradient * (inputs[1] - inputs[0]) / inputs[0].size
        ]

class SoftmaxLoss(FunctionNode):
    """
    A batched softmax loss, used for classification problems.

    IMPORTANT: do not swap the order of the inputs to this node!

    Usage: nn.SoftmaxLoss(logits, labels)
    Inputs:
        logits: a Node with shape (batch_size x num_classes). Each row
            represents the scores associated with that example belonging to a
            particular class. A score can be an arbitrary real number.
        labels: a Node with shape (batch_size x num_classes) that encodes the
            correct labels for the examples. All entries must be non-negative
            and the sum of values along each row should be 1.
    Output: a scalar Node (containing a single floating-point number)
    """
    @staticmethod
    def log_softmax(logits):
        log_probs = logits - np.max(logits, axis=1, keepdims=True)
        log_probs -= np.log(np.sum(np.exp(log_probs), axis=1, keepdims=True))
        return log_probs

    @staticmethod
    def _forward(*inputs):
        assert len(inputs) == 2, "Expected 2 inputs, got {}".format(len(inputs))
        assert inputs[0].ndim == 2, (
            "First input should have 2 dimensions, instead has {}".format(
                inputs[0].ndim))
        assert inputs[1].ndim == 2, (
            "Second input should have 2 dimensions, instead has {}".format(
                inputs[1].ndim))
        assert inputs[0].shape == inputs[1].shape, (
            "Input shapes should match, instead got {} and {}".format(
                format_shape(inputs[0].shape), format_shape(inputs[1].shape)))
        assert np.all(inputs[1] >= 0), (
            "All entries in the labels input must be non-negative")
        assert np.allclose(np.sum(inputs[1], axis=1), 1), (
            "Labels input must sum to 1 along each row")
        log_probs = SoftmaxLoss.log_softmax(inputs[0])
        return np.mean(-np.sum(inputs[1] * log_probs, axis=1))

    @staticmethod
    def _backward(gradient, *inputs):
        assert np.asarray(gradient).ndim == 0
        log_probs = SoftmaxLoss.log_softmax(inputs[0])
        return [
            gradient * (np.exp(log_probs) - inputs[1]) / inputs[0].shape[0],
            gradient * -log_probs / inputs[0].shape[0]
        ]

def gradients(loss, parameters):
    """
    Computes and returns the gradient of the loss with respect to the provided
    parameters.

    Usage: nn.gradients(loss, parameters)
    Inputs:
        loss: a SquareLoss or SoftmaxLoss node
        parameters: a list (or iterable) containing Parameter nodes
    Output: a list of Constant objects, representing the gradient of the loss
        with respect to each provided parameter.
    """

    assert isinstance(loss, (SquareLoss, SoftmaxLoss)), (
        "Loss must be a loss node, instead has type {!r}".format(
            type(loss).__name__))
    assert all(isinstance(parameter, Parameter) for parameter in parameters), (
        "Parameters must all have type {}, instead got types {!r}".format(
            Parameter.__name__,
            tuple(type(parameter).__name__ for parameter in parameters)))
    assert not hasattr(loss, "used"), (
        "Loss node has already been used for backpropagation, cannot reuse")

    loss.used = True

    nodes = set()
    tape = []

    def visit(node):
        if node not in nodes:
            for parent in node.parents:
                visit(parent)
            nodes.add(node)
            tape.append(node)

    visit(loss)
    nodes |= set(parameters)

    grads = {node: np.zeros_like(node.data) for node in nodes}
    grads[loss] = 1.0

    for node in reversed(tape):
        parent_grads = node._backward(
            grads[node], *(parent.data for parent in node.parents))
        for parent, parent_grad in zip(node.parents, parent_grads):
            grads[parent] += parent_grad

    return [Constant(grads[parameter]) for parameter in parameters]

def as_scalar(node):
    """
    Returns the value of a Node as a standard Python number. This only works
    for nodes with one element (e.g. SquareLoss and SoftmaxLoss, as well as
    DotProduct with a batch size of 1 element).
    """

    assert isinstance(node, Node), (
        "Input must be a node object, instead has type {!r}".format(
            type(node).__name__))
    assert node.data.size == 1, (
        "Node has shape {}, cannot convert to a scalar".format(
            format_shape(node.data.shape)))
    return node.data.item()
