use std::time::Duration;

pub enum Color {
    Red,
    White,
    Blue,
}

struct DutchFlagPrinter {
    column: usize,
}

impl DutchFlagPrinter {
    fn new(data: &mut [Color]) -> Self {
        let mut out = Self { column: 0 };
        out.reset(data);
        out
    }

    fn reset(&mut self, data: &mut [Color]) {
        self.column = 0;
        for _ in 0..data.len() {
            println!();
        }
    }

    fn write_line(data: &mut [Color], column: usize) {
        println!("\x1b[{}A", data.len());
        print!("\x1b[{}C", 2 * column);
        for color in data.iter() {
            match color {
                Color::Red => print!("\x1b[48;2;173;29;37m  \x1b[B\x1b[2D"),
                Color::White => print!("\x1b[48;2;255;255;255m  \x1b[B\x1b[2D"),
                Color::Blue => print!("\x1b[48;2;30;71;133m  \x1b[B\x1b[2D"),
            }
        }
        print!("\x1b[0m")
    }

    fn print_line(&mut self, data: &mut [Color]) {
        Self::write_line(data, self.column);
        self.column += 1;
    }
    fn reverse_print_line(&mut self, data: &mut [Color]) {
        self.column -= 1;
        Self::write_line(data, self.column);
    }
    fn print_flag_animation(&mut self, data: &mut [Color]) {
        let start = self.column;
        while self.column <= 3 * data.len() / 2 {
            self.print_line(data);
            std::thread::sleep(Duration::from_millis(50));
        }

        self.column = start;
        while self.column > 0 {
            self.reverse_print_line(data);
            std::thread::sleep(Duration::from_millis(50));
        }
    }
}

pub fn sort_dutch_flag(input: &mut [Color]) {
    let mut begin = 0;
    let mut end = input.len() - 1;
    let mut curr = 0;

    let mut flag_printer = DutchFlagPrinter::new(input);

    while curr < end {
        flag_printer.print_line(input);
        match input[curr] {
            Color::White => curr += 1,
            Color::Blue => {
                input.swap(curr, end);
                end -= 1;
            }
            Color::Red => {
                input.swap(curr, begin);
                begin += 1;
            }
        }
        std::thread::sleep(Duration::from_millis(50));
    }

    flag_printer.print_flag_animation(input);
    println!("\n\n\x1b[1mGOD BLESS THE DUTCH \x1b[0m\n");
    std::thread::sleep(Duration::from_millis(1500));
}
