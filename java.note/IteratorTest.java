import java.io.File;
import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Iterator;

public class IteratorTest {

    public static void main(String [] args) {
        FileIterator fileIterator = new FileIterator(new File(System.getProperty("user.dir")));
        while (fileIterator.hasNext()) {
            System.out.println(fileIterator.next());
        }
    }
}

// implements tree iterators in JAVA
class FileIterator implements Iterator<File> {

    // used to save the state of the current directory
    class WalkState {
        private WalkState(File[] currentFiles, int currentIndex) {
            this.currentFiles = currentFiles;
            this.currentIndex = currentIndex;
        }

        private File[] currentFiles; //all the files in the dirs
        private int currentIndex;

        private boolean isEnd() {
            return currentIndex >= currentFiles.length;
        }
    }

    Deque<WalkState> stateStack;
    private File nextFile;

    public FileIterator(File file) {
        stateStack = new ArrayDeque<WalkState>();
        if (file.isDirectory()) {
            stateStack.push(new WalkState(file.listFiles(), 0));
        } else {
            stateStack.push(new WalkState(new File[] { file }, 0));
        }
    }

    @Override
    public boolean hasNext() {
        // depth first traversal
        WalkState walkState = null;
        do {
            if (stateStack.isEmpty()) {
                return false;
            }
            walkState = stateStack.poll();
        } while (walkState.isEnd());

        nextFile = walkState.currentFiles[walkState.currentIndex++];
        stateStack.push(walkState);
        if (nextFile.isDirectory()) {
            // push the sub-directory in the stack
            stateStack.push(new WalkState(nextFile.listFiles(), 0));
            return hasNext();
        } else {
            return true;
        }
    }

    @Override
    public File next() {
        return nextFile;
    }

    @Override
    public void remove() {
        throw new UnsupportedOperationException(
                "Only support to traversal the dir");
    }
}



