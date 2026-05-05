import java.net.http.*;
import java.net.URI;
import java.time.Duration;
import java.util.concurrent.*;
import java.util.concurrent.atomic.*;

public class loadTest {
    private static final String TARGET_URL = "http://localhost:7072/api/v1/resource"; // adjust as needed
    private static final int THREAD_COUNT = 50;
    private static final int REQUESTS_PER_THREAD = 100;
    private static final HttpClient client = HttpClient.newBuilder()
            .connectTimeout(Duration.ofSeconds(5))
            .build();

    public static void main(String[] args) throws InterruptedException {
        AtomicInteger success = new AtomicInteger(0);
        AtomicInteger failure = new AtomicInteger(0);
        long startTime = System.currentTimeMillis();

        ExecutorService executor = Executors.newFixedThreadPool(THREAD_COUNT);
        CountDownLatch latch = new CountDownLatch(THREAD_COUNT);

        for (int t = 0; t < THREAD_COUNT; t++) {
            executor.submit(() -> {
                for (int i = 0; i < REQUESTS_PER_THREAD; i++) {
                    try {
                        HttpRequest request = HttpRequest.newBuilder()
                                .uri(URI.create(TARGET_URL))
                                .timeout(Duration.ofSeconds(3))
                                .GET()
                                .build();
                        HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
                        if (response.statusCode() == 200) {
                            success.incrementAndGet();
                        } else {
                            failure.incrementAndGet();
                        }
                    } catch (Exception e) {
                        failure.incrementAndGet();
                    }
                }
                latch.countDown();
            });
        }

        latch.await();
        executor.shutdown();
        long duration = System.currentTimeMillis() - startTime;

        System.out.println("Total requests: " + (THREAD_COUNT * REQUESTS_PER_THREAD));
        System.out.println("Successful: " + success.get());
        System.out.println("Failed: " + failure.get());
        System.out.println("Time (ms): " + duration);
        System.out.printf("Throughput: %.2f req/sec%n",
                (THREAD_COUNT * REQUESTS_PER_THREAD) / (duration / 1000.0));
    }
}