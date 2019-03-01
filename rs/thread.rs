use std::sync::mpsc;
use std::thread;
use std::time::SystemTime;

fn main() {
    let mut threads = vec![];
    let rx = {
        let (tx, rx) = mpsc::sync_channel(1000);
        for _i in 0..2 {
            let tx1 = mpsc::SyncSender::clone(&tx);
            threads.push(thread::spawn(|| generate(tx1)));
        }
        rx
    };

    let start = SystemTime::now();
    let mut sum = 0_u128;
    for n in rx {
        sum += n as u128;
    }
    let elapsed = start.elapsed().unwrap();

    for t in threads.into_iter() {
        t.join().unwrap();
    }
    println!("sum {}, elapsed {:?}", sum, elapsed);
}

fn generate(tx: mpsc::SyncSender<u64>) {
    let start = SystemTime::now();
    for i in 0..10_000_000 {
        tx.send(i).unwrap();
    }
    let elapsed = start.elapsed().unwrap();
    println!("generate elapsed {:?}", elapsed);
}
