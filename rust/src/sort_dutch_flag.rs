use rand::Rng;
use std::{
    io::{BufWriter, Write},
    thread::sleep,
    time::Duration,
};

#[derive(PartialEq)]
pub enum Color {
    Red,
    White,
    Blue,
}

impl Color {
    pub fn random() -> Self {
        match rand::rng().random_range(0..=2) {
            0 => Color::Red,
            1 => Color::White,
            2 => Color::Blue,
            _ => panic!("rng generated wrong type"),
        }
    }
}

struct DutchFlagPrinter {
    column: usize,
    buf: BufWriter<std::io::Stdout>,
}

#[allow(dead_code)]
impl DutchFlagPrinter {
    fn new(data: &mut [Color]) -> Self {
        let mut out = Self {
            column: 0,
            buf: BufWriter::new(std::io::stdout()),
        };
        out.reset(data);
        print!("\x1b[?25l");
        out
    }

    fn reset(&mut self, data: &mut [Color]) {
        self.column = 0;
        for _ in 0..data.len() {
            println!()
        }
    }

    fn write_line(&mut self, data: &mut [Color], column: usize) {
        (|| -> std::io::Result<()> {
            write!(self.buf, "\x1b[{}A", data.len())?;
            write!(self.buf, "\n\x1b[{}C", 2 * column)?;
            for color in data.iter() {
                match color {
                    Color::Red => write!(self.buf, "\x1b[48;2;173;29;37m  \x1b[B\x1b[2D")?,
                    Color::White => write!(self.buf, "\x1b[48;2;255;255;255m  \x1b[B\x1b[2D")?,
                    Color::Blue => write!(self.buf, "\x1b[48;2;30;71;133m  \x1b[B\x1b[2D")?,
                };
            }
            write!(self.buf, "\x1b[0m")?;
            self.buf.flush()?;
            Ok(())
        })()
        .expect("failed to write to stdout");
    }

    fn del_line(&mut self, data: &mut [Color], column: usize) {
        (|| -> std::io::Result<()> {
            write!(self.buf, "\x1b[{}A", data.len())?;
            write!(self.buf, "\x1b[{}C", 2 * column)?;
            for _ in 0..=data.len() {
                write!(self.buf, "  \x1b[B\x1b[2D")?;
            }
            self.buf.flush()?;
            Ok(())
        })()
        .expect("failed to write to stdout");
    }

    fn print_line(&mut self, data: &mut [Color]) {
        self.write_line(data, self.column);
        self.column += 1;
    }

    fn print_flag_animation(&mut self, data: &mut [Color]) {
        let sleep_time = Duration::from_micros((500000 / data.len()) as u64);
        let start = self.column;
        let max = 3 * data.len() / 2;

        while self.column <= max {
            self.print_line(data);
            sleep(sleep_time);
        }

        self.column = start;
        while self.column > 0 {
            self.column -= 1;
            self.write_line(data, self.column);
            sleep(sleep_time);
        }
    }
}

impl Drop for DutchFlagPrinter {
    fn drop(&mut self) {
        print!("\x1b[?25h");
    }
}

pub fn sort_dutch_flag(input: &mut [Color]) {
    let sleep_time = Duration::from_micros((1500000 / input.len()) as u64);
    let mut begin = 0;
    let mut end = input.len() - 1;
    let mut curr = 0;

    let mut flag_printer = DutchFlagPrinter::new(input);

    while curr <= end {
        flag_printer.print_line(input);

        match input[curr] {
            Color::White => {
                while input[curr] == Color::White {
                    curr += 1;
                }
            }

            Color::Blue => {
                input.swap(curr, end);
                while input[end] == Color::Blue {
                    end -= 1;
                }
            }

            Color::Red => {
                input.swap(curr, begin);
                while input[begin] == Color::Red {
                    begin += 1;
                }
                curr = begin;
            }
        }

        sleep(sleep_time);
    }

    flag_printer.print_flag_animation(input);
    println!("\n\n\x1b[1mGOD BLESS THE DUTCH \x1b[0m");
    sleep(Duration::from_millis(1500));
}
